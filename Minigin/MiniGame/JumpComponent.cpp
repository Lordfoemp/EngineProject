#include "MiniGamePCH.h"
#include "JumpComponent.h"

#include <GameObject.h>

#include <ColliderComponent.h>
#include <PhysicsComponent.h>
#include <TransformComponent.h>
#include <LevelComponent.h>

#include <Locator.h>
#include <SceneManager.h>

#include <Scene.h>
#include "../MiniGame/Scene_01.h"
#include "../MiniGame/Scene_02.h"
#include "../MiniGame/Scene_03.h"

#include "Cube.h"
#include "Level.h"
#include "Connection.h"
#include "QBERT.h"

Helheim::JumpComponent::JumpComponent(Helheim::GameObject* pParentObject)
					   : Component(pParentObject, false)
					   , m_CurrentCubeIndex(0)
{}

void Helheim::JumpComponent::Initialize(Scene* )	 //pParentScene
{}
void Helheim::JumpComponent::Update(const float )	//elapsedSec
{}
void Helheim::JumpComponent::FixedUpdate(const float )//timeEachUpdate
{}

Helheim::LevelComponent* Helheim::JumpComponent::FindLevelComponent()
{
	Scene* pScene = Locator::GetSceneService()->GetActiveScene();
	Scene_01* pScene01{ dynamic_cast<Scene_01*>(pScene) };
	if (pScene01)
		return pScene01->GetLevel()->GetLevelComponent();
	else
	{
		Scene_02* pScene02{ dynamic_cast<Scene_02*>(pScene) };
		if (pScene02)
			return pScene02->GetLevel()->GetLevelComponent();
		else
		{
			Scene_03* pScene03{ dynamic_cast<Scene_03*>(pScene) };
			if (pScene03)
				return pScene03->GetLevel()->GetLevelComponent();
		}
	}

	return nullptr;
}

Helheim::Cube* Helheim::JumpComponent::FindConnectingCube(std::vector<Connection*>& pConnections, const glm::vec3& currentPositionQBERT, const bool jumpLeft, const bool jumpUp)
{
	bool connectingCubeFound{ false };
	Connection* pConnection{ nullptr };
	Cube* pConnectingCube{ nullptr };
	glm::vec3 connectingCubePosition{};
	const size_t nbrOfConnection{ pConnections.size() };
	for (size_t i{}; i < nbrOfConnection; ++i)
	{
		pConnection = pConnections[i];

		// Check if the connecting cube is on the left, down of the QBERT
		pConnectingCube = pConnection->GetCube2();
		connectingCubePosition = pConnectingCube->GetGameObject()->GetComponent<TransformComponent>()->GetPosition();

		// Jump Left
		bool jumpLeftDown{ jumpLeft && !jumpUp };
		if (jumpLeftDown)
		{
			if (connectingCubePosition.x < currentPositionQBERT.x && connectingCubePosition.y > currentPositionQBERT.y + 20.f)
			{
				connectingCubeFound = true;
				return pConnectingCube;
			}
		}
		bool jumpLeftUp{ jumpLeft && jumpUp };
		if (jumpLeftUp)
		{
			if (currentPositionQBERT.x > connectingCubePosition.x && currentPositionQBERT.y + 20.f > connectingCubePosition.y)
			{
				connectingCubeFound = true;
				return pConnectingCube;
			}
		}
		// Jump Right
		bool jumpRightDown{ !jumpLeft && !jumpUp };
		if (jumpRightDown)
		{
			if (currentPositionQBERT.x < connectingCubePosition.x && connectingCubePosition.y > currentPositionQBERT.y + 20.f)
			{
				connectingCubeFound = true;
				return pConnectingCube;
			}
		}
		bool jumpRightUp{ !jumpLeft && jumpUp };
		if (jumpRightUp)
		{
			if (currentPositionQBERT.x < connectingCubePosition.x && currentPositionQBERT.y + 20.f > connectingCubePosition.y)
			{
				connectingCubeFound = true;
				return pConnectingCube;
			}
		}
	}

	return nullptr;
}

bool Helheim::JumpComponent::Jump(const bool jumpLeft, const bool jumpUp)
{
	// Get current data of QBERT
	TransformComponent* pTransformComponent{ m_pParentObject->GetComponent<TransformComponent>() };
	PhysicsComponent* pPhysicsComponent{ m_pParentObject->GetComponent<PhysicsComponent>() };
	ColliderComponent* pColliderComponent{ m_pParentObject->GetComponent<ColliderComponent>() };
	glm::vec3 currentPositionQBERT{ pTransformComponent->GetPosition() };

	// Retrieve the level from the Level Game Object
	LevelComponent* pLevelComponent{ FindLevelComponent() };

	// Get all the needed data for easy access
	std::vector<Cube*> pCubes = pLevelComponent->GetCubes();
	Cube* pCurrentCube{ pCubes[m_CurrentCubeIndex] };
	std::vector<Connection*> pConnections = pCurrentCube->GetConnections();

	// Find the connection that is on the left and lower then the player
	Cube* pConnectingCube{ FindConnectingCube(pConnections, currentPositionQBERT, jumpLeft, jumpUp) };

	if (pConnectingCube)
	{
		glm::vec3 connectingCubePosition = pConnectingCube->GetGameObject()->GetComponent<TransformComponent>()->GetPosition();

		// Set the new current index of the new cube
		m_CurrentCubeIndex = std::distance(pCubes.begin(), std::find(pCubes.begin(), pCubes.end(), pConnectingCube));
		std::cout << "Current cube index: " << m_CurrentCubeIndex << '\n';

		// Set the Character position to the new position and update the m_CurrentCubeIndex	
		//pTransformComponent->SetPosition(connectingCubePosition.x + 10, connectingCubePosition.y - 20, 0);
		pPhysicsComponent->SetJumpForce(100.f, jumpLeft, jumpUp);
		pPhysicsComponent->SetJumping();
		//pColliderComponent->SetCollisionState(ColliderComponent::CollisionState::FALLING);
		pColliderComponent->SetTargetCubeIndex(m_CurrentCubeIndex);
		pColliderComponent->SetCollisionInformation(jumpLeft, jumpUp);

		if (m_pParentObject->GetName().find("Player") != std::string::npos)
		{
			return pLevelComponent->ColorCube(m_CurrentCubeIndex);
		}		
	}
	return false;
}