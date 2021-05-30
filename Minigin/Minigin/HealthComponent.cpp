#include "MiniginPCH.h"
#include "HealthComponent.h"

// dae Includes
#include "GameObject.h"

// Helheim Includes
#include "Timer.h"
#include "TextComponent.h"
#include "Observer.h"

Helheim::HealthComponent::HealthComponent(Helheim::GameObject* pParentObject, const int maxHealth, const int maxLives)
		: Component(pParentObject, false)
		, m_StartHealth(maxHealth)
		, m_CurrentHealth(maxHealth)
		, m_Lives(maxLives)
		, m_Event(Observer::OBSERVER_EVENTS::NO_EVENT)
{}

void Helheim::HealthComponent::Initialize(Scene*) // pParentScene
{}
void Helheim::HealthComponent::Update(const float)
{
	if (m_CurrentHealth <= 0)
	{
		NotifyObservers(m_pParentObject, m_Event);
		m_CurrentHealth = m_StartHealth;
	}
}
void Helheim::HealthComponent::FixedUpdate(const float)
{}