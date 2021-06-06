#include "MiniGamePCH.h"
#include "JumpComponent.h"

#include <GameObject.h>

#include "ColliderComponent.h"
#include <PhysicsComponent.h>
#include <TransformComponent.h>
#include "LevelComponent.h"
#include "CubeComponent.h"

#include <Locator.h>
#include <SceneManager.h>

#include <Scene.h>
#include "../MiniGame/Scene_01.h"
#include "../MiniGame/Scene_02.h"
#include "../MiniGame/Scene_03.h"

#include "Cube.h"
#include "Disc.h"
#include "Level.h"
#include "Connection.h"
//#include "QBERT.h"

Helheim::JumpComponent::JumpComponent(Helheim::GameObject* pParentObject)
					   : Component(pParentObject, false)
					   , m_CurrentCubeIndex(0)
					   , m_CurrentDiscIndex(0)
{}

void Helheim::JumpComponent::Initialize(Scene* )		//pParentScene
{}
void Helheim::JumpComponent::PostInitialize(Scene*)		//pParentScene
{
}
void Helheim::JumpComponent::Update(const float )		//elapsedSec
{}
void Helheim::JumpComponent::FixedUpdate(const float )	//timeEachUpdate
{}

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
	std::vector<GameObject*> pCubes = pLevelComponent->GetCubes();
	GameObject* pCurrentCube{ pCubes[m_CurrentCubeIndex] };
	std::vector<Connection*> pConnections = pCurrentCube->GetComponent<CubeComponent>()->GetConnections();

	// Find the connection that is on the left and lower then the player
	GameObject* pConnectingCube{ FindConnectingCube(pConnections, currentPositionQBERT, jumpLeft, jumpUp) };
	// If we found a cube then fix all the stuffs to get there :)
	if (pConnectingCube)
	{
		// Set the new current index of the new cube
		m_CurrentCubeIndex = std::distance(pCubes.begin(), std::find(pCubes.begin(), pCubes.end(), pConnectingCube));

		// Update the needed stuffs in Physics component
		pPhysicsComponent->SetJumpForce(100.f, jumpLeft, jumpUp);
		pPhysicsComponent->SetJumping();
		// Update the needed stuffs in Collider component
		pColliderComponent->SetTargetCubeIndex(m_CurrentCubeIndex);
		pColliderComponent->SetCollisionInformation(jumpLeft, jumpUp);	
	}
	else
	{
		// DIE

	}
	return false;
}
void Helheim::JumpComponent::Escape(const bool jumpLeft, const bool jumpUp)
{
	// Get current data of QBERT
	TransformComponent* pTransformComponent{ m_pParentObject->GetComponent<TransformComponent>() };
	PhysicsComponent* pPhysicsComponent{ m_pParentObject->GetComponent<PhysicsComponent>() };
	ColliderComponent* pColliderComponent{ m_pParentObject->GetComponent<ColliderComponent>() };
	glm::vec3 currentPositionQBERT{ pTransformComponent->GetPosition() };

	// Retrieve the level from the Level Game Object
	LevelComponent* pLevelComponent{ FindLevelComponent() };

	// Get all the needed data for easy access
	std::vector<GameObject*> pCubes = pLevelComponent->GetCubes();
	GameObject* pCurrentCube{ pCubes[m_CurrentCubeIndex] };
	std::vector<Connection*> pConnections = pCurrentCube->GetComponent<CubeComponent>()->GetConnections();

	GameObject* pConnectingDisc{ FindConnectingDisc(pConnections, currentPositionQBERT, jumpLeft, jumpUp) };
	if (pConnectingDisc)
	{
		// Update the needed stuffs in Physics component
		pPhysicsComponent->SetJumpForce(100.f, pConnectingDisc->GetComponent<TransformComponent>()->GetPosition().x < currentPositionQBERT.x, jumpUp);
		pPhysicsComponent->SetJumping();

		// Update the needed stuffs in Collider component
		std::vector<GameObject*> pDiscs{ pLevelComponent->GetDiscs() };
		m_CurrentDiscIndex = std::distance(pDiscs.begin(), std::find(pDiscs.begin(), pDiscs.end(), pConnectingDisc));
		pColliderComponent->SetTargetDiscIndex(m_CurrentDiscIndex);
		pColliderComponent->SetCollisionInformation(pConnectingDisc->GetComponent<TransformComponent>()->GetPosition().x < currentPositionQBERT.x, jumpUp);

		pColliderComponent->SetCharacterState(ColliderComponent::CharacterState::ESCAPE);
		pColliderComponent->SetCollisionState(ColliderComponent::CollisionState::JUMPING);
	}
}

Helheim::LevelComponent* Helheim::JumpComponent::FindLevelComponent()
{
	Scene* pScene = Locator::GetSceneService()->GetActiveGameScene();
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

Helheim::GameObject* Helheim::JumpComponent::FindConnectingCube(std::vector<Connection*>& pConnections, const glm::vec3& currentPositionQBERT, const bool jumpLeft, const bool jumpUp)
{
	bool connectingCubeFound{ false };
	Connection* pConnection{ nullptr };
	GameObject* pConnectingCube{ nullptr };
	glm::vec3 connectingCubePosition{};
	const size_t nbrOfConnection{ pConnections.size() };
	for (size_t i{}; i < nbrOfConnection; ++i)
	{
		pConnection = pConnections[i];

		// Check if the connecting cube is on the left, down of the QBERT
		pConnectingCube = pConnection->GetCube2();
		connectingCubePosition = pConnectingCube->GetComponent<TransformComponent>()->GetPosition();

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
Helheim::GameObject* Helheim::JumpComponent::FindConnectingDisc(std::vector<Connection*>& pConnections, const glm::vec3& , const bool , const bool )
{
	//bool connectingCubeFound{ false };
	Connection* pConnection{ nullptr };
	GameObject* pConnectingDisc{ nullptr };
	glm::vec3 connectingDiscPosition{};
	const size_t nbrOfConnection{ pConnections.size() };
	for (size_t i{}; i < nbrOfConnection; ++i)
	{
		pConnection = pConnections[i];

		// Check if the connecting cube is on the left, down of the QBERT
		pConnectingDisc = pConnection->GetDisc();
		if (pConnectingDisc)
		{
			m_CurrentDiscIndex = i;
			return pConnectingDisc;
		}
	}

	return nullptr;
}
