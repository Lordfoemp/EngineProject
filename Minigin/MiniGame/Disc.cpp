#include "MiniGamePCH.h"
#include "Disc.h"

#include "Locator.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "QBERT.h"

Helheim::Disc::Disc()
			  : m_Height(10)
			  , m_Width(16)
			  , m_pDiscGO(nullptr)
			  , m_pConnection(nullptr)
			  , m_pTexture_01(nullptr)
			  , m_Used(false)
{}

void Helheim::Disc::Initialize(Scene * pCurrentScene, const glm::vec3 & pos, const std::string & folderpath)
{
	// Parameters
	glm::vec3 position = pos;
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale = glm::vec3{ 1.5f, 1.5f, 1.5f };

	// GameObject
	m_pDiscGO = new Helheim::GameObject(position, rotation, scale);

	// Componenets
	m_pTexture_01 = new Helheim::TextureComponent("Disc_01.png", folderpath, m_pDiscGO);
	m_pTexture_01->SetCanRenderComponent(true);
	m_pDiscGO->AddComponent(m_pTexture_01);

	m_pDiscGO->SetName("Disc");

	// Add to scene
	pCurrentScene->AddGameObject(m_pDiscGO);
}
void Helheim::Disc::Update(const float elapsedSec)
{
	if (m_Used)
		return;

	QBERT* qbert{ Locator::GetSceneService()->GetActiveScene()->GetQBERT() };
	
	GameObject* pPlayerGO{ qbert->GetGameObject_QBERT_Char() };
	ColliderComponent* pPlayerCollider{ pPlayerGO->GetComponent<ColliderComponent>() };
	ColliderComponent::CollisionState collisionState{ pPlayerCollider->GetCollisionState() };
	ColliderComponent::CharacterState characterState{ pPlayerCollider->GetCharacterState() };
	if (collisionState == ColliderComponent::CollisionState::ON_GROUND && 
		characterState == ColliderComponent::CharacterState::ESCAPE)
	{
		TransformComponent* pTransformComponent{ m_pDiscGO->GetComponent<TransformComponent>() };
		// Calculate direction vector to end point
		glm::vec3 startPosition{ pTransformComponent->GetPosition() };
		glm::vec3 endPosition{ 640 / 2 + 13, 50, 0 };
		glm::vec3 directionVector{ endPosition - startPosition };

		// Edit position with the direction vector
		glm::vec3 newPosition{};
		newPosition.x = startPosition.x + (directionVector.x * elapsedSec);
		newPosition.y = startPosition.y + (directionVector.y * elapsedSec);
		newPosition.z = startPosition.z + (directionVector.z * elapsedSec);

		pTransformComponent->SetPosition(newPosition.x, newPosition.y, newPosition.z);

		if (newPosition.y < endPosition.y + 1)
		{
			pPlayerCollider->Reset();
			qbert->Reset(GetGameObject()->GetComponent<TransformComponent>()->GetPosition());
			m_Used = true;

			m_pTexture_01->SetCanRenderComponent(false);
		}
	}

	
}