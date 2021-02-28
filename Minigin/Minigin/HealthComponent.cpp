#include "MiniginPCH.h"
#include "HealthComponent.h"

// dae Includes
#include "GameObject.h"

// Helheim Includes
#include "Timer.h"
#include "TextComponent.h"
#include "Observer.h"

Helheim::HealthComponent::HealthComponent(std::shared_ptr<dae::GameObject>& pParentObject, const int maxHealth, const int maxLives)
		: Component(pParentObject, false)
		, m_Health(maxHealth)
		, m_Lives(maxLives)
{
	/*if (!pParentObject->HasComponent<Helheim::TextComponent>())
	{
		m_pTextComponent = std::make_shared<Helheim::TextComponent>(pParentObject, "0", pFont);
		pParentObject->AddComponent(m_pTextComponent);
	}
	else
		m_pTextComponent = pParentObject->GetComponent<Helheim::TextComponent>();*/
}

void Helheim::HealthComponent::Initialize()
{}
void Helheim::HealthComponent::Update()
{
	if (m_Health <= 0)
	{
		NotifyObservers();
	}
}
void Helheim::HealthComponent::FixedUpdate()
{}

void Helheim::HealthComponent::NotifyObservers()
{
	const size_t observersAmount{ m_pObservers.size() };
	auto pParentObject = GetParentObject();
	for (size_t i{}; i < observersAmount; i++)
	{		
		m_pObservers[i]->OnNotify(pParentObject, Observer::OBSERVER_EVENTS::PLAYER_DIED );
	}
}