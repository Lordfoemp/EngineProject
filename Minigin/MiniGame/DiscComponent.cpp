#include "MiniGamePCH.h"
#include "DiscComponent.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "QBERTComponent.h"

#include "SceneManager.h"
#include "Scene.h"

Helheim::DiscComponent::DiscComponent(Helheim::GameObject* pParentObject)
					   : Component(pParentObject, false)
					   , m_IsUsed(false)
					   , m_IsActive(false)
					   , m_GoingRight(false)
					   , m_pTextureComponent(nullptr)
{}

void Helheim::DiscComponent::Initialize(Scene* )	//pParentScene
{}
void Helheim::DiscComponent::PostInitialize(Scene* )	//pParentScene
{
	m_pTextureComponent = m_pParentObject->GetComponent<TextureComponent>();
}
void Helheim::DiscComponent::Update(const float elapsedSec)	//elapsedSec
{
	if (m_IsUsed)
		return;

	if (m_IsActive)
	{
		UpdatePosition(elapsedSec);
		UpdateNotifier();
	}	
}
void Helheim::DiscComponent::FixedUpdate(const float )	//timeEachUpdate
{}

void Helheim::DiscComponent::UpdatePosition(const float elapsedSec)
{
	TransformComponent* pTransformComponent{ m_pParentObject->GetComponent<TransformComponent>() };
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

	if (startPosition.x < endPosition.x && !m_GoingRight)
	{
		m_GoingRight = true;
	}
}
void Helheim::DiscComponent::UpdateNotifier()
{
	glm::vec3 newPosition{ m_pParentObject->GetComponent<TransformComponent>()->GetPosition() };
	glm::vec3 endPosition{ 640 / 2 + 13, 50, 0 };
	if (newPosition.y < endPosition.y + 3/* && m_GoingRight*/)
	{
		NotifyObservers(m_pParentObject, Observer::OBSERVER_EVENTS::DELETE_DISC);

		m_IsUsed = true;
	}
	/*else if (newPosition.y > endPosition.y - 3 && !m_GoingRight)
	{
		NotifyObservers(m_pParentObject, Observer::OBSERVER_EVENTS::DELETE_DISC);

		m_IsUsed = true;
	}*/
}
