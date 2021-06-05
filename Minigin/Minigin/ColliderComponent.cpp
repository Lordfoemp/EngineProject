#include "MiniginPCH.h"
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
						   , m_Rect{ 0,0,0 }
						   , m_Pos{}
						   , m_Color{ 0, 255, 255 }
						   , m_CollisionState{ CollisionState::FALLING }
						
{}

void Helheim::ColliderComponent::Reset()
{
	oldpos = FLT_MAX;
	SetCharacterState(CharacterState::JUMPING);
	SetCollisionState(CollisionState::FALLING);
}

void Helheim::ColliderComponent::Initialize(Scene* )//pParentScene
{

}
void Helheim::ColliderComponent::Update(const float)//elapsedSec
{
	if (m_CharacterState != CharacterState::ESCAPE)
	{
		TransformComponent* pTransformComponent_Char{ m_pParentObject->GetComponent<TransformComponent>() };
		//LevelComponent* pLevelComponent{ m_pLevelGO->GetComponent<LevelComponent>() };

		auto scene{ Locator::GetSceneService()->GetActiveScene() };
		auto objects{ scene->GetObjects() };

		std::vector<GameObject*> pCubes{};
		for (size_t i{}; i < objects.size(); ++i)
		{
			GameObject* pObject{ objects[i] };
			if (pObject->GetName() == "Cube")
			{
				pCubes.push_back(pObject);
			}
		}
		auto object{ pCubes[m_TargetCubeIndex] };
		const glm::vec3 cubePosition{ object->GetComponent<TransformComponent>()->GetPosition() };
		const glm::vec3 charPosition{ pTransformComponent_Char->GetPosition() };

		{	// Falling/Jumping check
			if (oldpos < charPosition.y)
				m_CollisionState = CollisionState::FALLING;
			if (oldpos > charPosition.y)
				m_CollisionState = CollisionState::JUMPING;
		}

		if (m_CollisionState != CollisionState::JUMPING)
		{	// Ground check
			if (cubePosition.y <= charPosition.y + 20 && m_CollisionState != CollisionState::JUMPING)
			{
				m_CollisionState = CollisionState::ON_GROUND;
				m_pParentObject->GetComponent<TransformComponent>()->SetPosition(cubePosition.x + 10, cubePosition.y - 20, 0);
				m_pParentObject->GetComponent<PhysicsComponent>()->ResetFallSpeed();

				std::cout << "currentPosition 2: " << cubePosition.y - 20 << '\n';

			}
			else if (cubePosition.y != charPosition.y + 20 && m_CollisionState != CollisionState::FALLING)
			{
				m_CollisionState = CollisionState::FALLING;
			}
		}
		oldpos = charPosition.y;
	}
	else
	{
		TransformComponent* pTransformComponent_Char{ m_pParentObject->GetComponent<TransformComponent>() };
		//LevelComponent* pLevelComponent{ m_pLevelGO->GetComponent<LevelComponent>() };

		auto scene{ Locator::GetSceneService()->GetActiveScene() };
		auto objects{ scene->GetObjects() };

		std::vector<GameObject*> pDiscs{};
		for (size_t i{}; i < objects.size(); ++i)
		{
			GameObject* pObject{ objects[i] };
			if (pObject->GetName() == "Disc")
			{
				pDiscs.push_back(pObject);
			}
		}
		auto object{ pDiscs[m_TargetDiscIndex] };
		const glm::vec3 cubePosition{ object->GetComponent<TransformComponent>()->GetPosition() };
		const glm::vec3 charPosition{ pTransformComponent_Char->GetPosition() };

		//if (m_CollisionState != CollisionState::ON_GROUND)
		{	// Falling/Jumping check
			if (oldpos < charPosition.y)
				m_CollisionState = CollisionState::FALLING;
			if (oldpos > charPosition.y)
				m_CollisionState = CollisionState::JUMPING;
		}

		if (m_CollisionState != CollisionState::JUMPING)
		{	// Ground check
			if (cubePosition.y <= charPosition.y + 20 && m_CollisionState != CollisionState::JUMPING)
			{
				m_CollisionState = CollisionState::ON_GROUND;
				m_pParentObject->GetComponent<TransformComponent>()->SetPosition(cubePosition.x - 5, cubePosition.y - 20, 0);
				m_pParentObject->GetComponent<PhysicsComponent>()->ResetFallSpeed();

				//std::cout << "currentPosition 2: " << cubePosition.y - 40 << '\n';

			}
			else if (cubePosition.y != charPosition.y + 20 && m_CollisionState != CollisionState::FALLING)
			{
				m_CollisionState = CollisionState::FALLING;
			}
		}
		oldpos = charPosition.y;
	}
}
void Helheim::ColliderComponent::FixedUpdate(const float )//timeEachUpdate
{

}