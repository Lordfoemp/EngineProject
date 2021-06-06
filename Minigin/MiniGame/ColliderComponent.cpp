#include "MiniGamePCH.h"
#include "ColliderComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "LevelComponent.h"
#include "PhysicsComponent.h"

#include "Locator.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Renderer.h"

Helheim::ColliderComponent::ColliderComponent(Helheim::GameObject* pParentObject)
						   : Component(pParentObject, false)
						   , m_OldYPosition{ FLT_MAX }
						   , m_JumpingLeft{ false }
						   , m_JumpingUp{ false }
						   , m_Rect{}
						   , m_Pos{}
						   , m_Color{}
						   , m_TargetCubeIndex{}
						   , m_TargetDiscIndex{}
						   , m_CollisionState{ CollisionState::FALLING }
						   , m_CharacterState{ CharacterState::JUMPING }
						   , m_pLevelGO{ nullptr }
{}

void Helheim::ColliderComponent::Reset()
{
	m_OldYPosition = FLT_MAX;
	SetCharacterState(CharacterState::JUMPING);
	SetCollisionState(CollisionState::FALLING);
}

void Helheim::ColliderComponent::Initialize(Scene* )//pParentScene
{

}
void Helheim::ColliderComponent::PostInitialize(Scene*)//pParentScene
{
}
void Helheim::ColliderComponent::Update(const float)//elapsedSec
{
	if (m_CharacterState != CharacterState::ESCAPE)
		UpdateCollision_Cubes();
	else
		UpdateCollision_Discs();
}
void Helheim::ColliderComponent::FixedUpdate(const float )//timeEachUpdate
{

}

void Helheim::ColliderComponent::UpdateCollision_Cubes()
{
	TransformComponent* pTransformComponent_Char{ m_pParentObject->GetComponent<TransformComponent>() };

	GameObject* pLevelGO{ Locator::GetSceneService()->GetActiveGameScene()->GetObjectByName("Level") };
	std::vector<GameObject*> pCubes{ pLevelGO->GetComponent<LevelComponent>()->GetCubes() };

	GameObject* pCube{ pCubes[m_TargetCubeIndex] };
	const glm::vec3 cubePosition{ pCube->GetComponent<TransformComponent>()->GetPosition() };
	const glm::vec3 charPosition{ pTransformComponent_Char->GetPosition() };

	{	// Falling/Jumping check
		if (m_OldYPosition < charPosition.y)
			m_CollisionState = CollisionState::FALLING;
		if (m_OldYPosition > charPosition.y && m_CollisionState != CollisionState::ON_GROUND)
			m_CollisionState = CollisionState::JUMPING;
	}

	if (m_CollisionState != CollisionState::JUMPING)
	{	// Ground check
		if (cubePosition.y <= charPosition.y + 20 && m_CollisionState != CollisionState::ON_GROUND)
		{
			m_CollisionState = CollisionState::ON_GROUND;
			m_pParentObject->GetComponent<TransformComponent>()->SetPosition(cubePosition.x + 10, cubePosition.y - 20, 0);
			m_pParentObject->GetComponent<PhysicsComponent>()->ResetFallSpeed();

			//std::cout << "currentPosition 2: " << cubePosition.y - 20 << '\n';
			NotifyObservers(m_pParentObject, Observer::OBSERVER_EVENTS::COLOR_CUBE);
		}
		else if (cubePosition.y != charPosition.y + 20 && m_CollisionState != CollisionState::FALLING)
		{
			m_CollisionState = CollisionState::FALLING;
		}
	}
	m_OldYPosition = charPosition.y;
}
void Helheim::ColliderComponent::UpdateCollision_Discs()
{
	TransformComponent* pTransformComponent_Char{ m_pParentObject->GetComponent<TransformComponent>() };
	auto scene{ Locator::GetSceneService()->GetActiveGameScene() };
	auto objects{ scene->GetObjects() };

	GameObject* pLevelGO{ Locator::GetSceneService()->GetActiveGameScene()->GetObjectByName("Level") };
	std::vector<GameObject*> pDiscs{ pLevelGO->GetComponent<LevelComponent>()->GetDiscs() };
	GameObject* pDisc{ pDiscs[m_TargetDiscIndex] };
	const glm::vec3 discPosition{ pDisc->GetComponent<TransformComponent>()->GetPosition() };
	const glm::vec3 charPosition{ pTransformComponent_Char->GetPosition() };

	// If the qbert is jumping check for when it is falling
	if (m_CollisionState == CollisionState::JUMPING)
	{
		if (m_OldYPosition < charPosition.y)
			m_CollisionState = CollisionState::FALLING;
	}
	// If the qbert is falling check if it is touching the target disc
	if (m_CollisionState == CollisionState::FALLING)
	{
		// Ground check
		std::cout << "discPosition: " << discPosition.y << '\n';
		std::cout << "charPosition: " << charPosition.y << '\n';
		if (discPosition.y <= charPosition.y + 10 && m_CollisionState != CollisionState::ON_GROUND)
		{
			m_CollisionState = CollisionState::ON_GROUND;
			m_pParentObject->GetComponent<TransformComponent>()->SetPosition(discPosition.x - 5, discPosition.y - 20, 0);
			m_pParentObject->GetComponent<PhysicsComponent>()->ResetFallSpeed();

			//std::cout << "currentPosition 2: " << cubePosition.y - 40 << '\n';
			NotifyObservers(m_pParentObject, Observer::OBSERVER_EVENTS::ACTIVATE_DISC);
		}
	}
	// If on the ground keep on tracking the current 
	if (m_CollisionState == CollisionState::ON_GROUND)
	{
		m_pParentObject->GetComponent<TransformComponent>()->SetPosition(discPosition.x - 5, discPosition.y - 20, 0);
	}
	// remeber the Y position
	m_OldYPosition = charPosition.y;


	//if (m_CollisionState != CollisionState::JUMPING)
	//{	// Falling/Jumping check
	//	if (m_OldYPosition < charPosition.y)
	//		m_CollisionState = CollisionState::FALLING;
	//	if (m_OldYPosition >= charPosition.y)
	//		m_CollisionState = CollisionState::JUMPING;
	//}

	//if (m_CollisionState != CollisionState::JUMPING)
	//{	// Ground check
	//	std::cout << "discPosition: " << discPosition.y << '\n';
	//	std::cout << "charPosition: " << charPosition.y << '\n';
	//	if (discPosition.y <= charPosition.y + 10 && m_CollisionState != CollisionState::ON_GROUND)
	//	{
	//		m_CollisionState = CollisionState::ON_GROUND;
	//		m_pParentObject->GetComponent<TransformComponent>()->SetPosition(discPosition.x - 5, discPosition.y - 20, 0);
	//		m_pParentObject->GetComponent<PhysicsComponent>()->ResetFallSpeed();

	//		//std::cout << "currentPosition 2: " << cubePosition.y - 40 << '\n';
	//		NotifyObservers(m_pParentObject, Observer::OBSERVER_EVENTS::ACTIVATE_DISC);
	//	}
	//	else if (discPosition.y != charPosition.y + 20 && m_CollisionState != CollisionState::FALLING)
	//	{
	//		m_CollisionState = CollisionState::FALLING;
	//	}
	//}
	//m_OldYPosition = charPosition.y;
}