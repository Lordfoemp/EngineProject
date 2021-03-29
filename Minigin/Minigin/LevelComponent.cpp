#include "MiniginPCH.h"
#include "LevelComponent.h"

// dae Includes
#include "GameObject.h"

// Helheim Includes
#include "Timer.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"

Helheim::LevelComponent::LevelComponent(Helheim::GameObject* pParentObject, const glm::vec3& color)
						: Component(pParentObject, false)
						, m_StartColor(color)
						, m_CurrentColor(color)
						, m_Event(Observer::OBSERVER_EVENTS::NO_EVENT)
{
	if (!pParentObject->HasComponent<Helheim::TextureComponent>())
	{
		m_pTextureComponent = new Helheim::TextureComponent("Spritesheet.png", pParentObject);
		pParentObject->AddComponent(m_pTextureComponent);
	}
	else
		m_pTextureComponent = pParentObject->GetComponent<Helheim::TextureComponent>();
}

void Helheim::LevelComponent::Initialize()
{}
void Helheim::LevelComponent::Update(const float)
{
	if (m_StartColor != m_CurrentColor)
	{
		NotifyObservers(m_pParentObject, m_Event);
	}
}
void Helheim::LevelComponent::FixedUpdate(const float)
{}