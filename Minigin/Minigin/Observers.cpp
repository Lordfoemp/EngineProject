#include "MiniginPCH.h"
#include "Observers.h"

// Helheim includes
#include "TextComponent.h"
#include "HealthComponent.h"
#include "GameObject.h"


Helheim::Health::Health(const std::shared_ptr<dae::GameObject>& pMessageReciever)
				: m_pMessageReceiver(pMessageReciever)
{}
void Helheim::Health::OnNotify(std::shared_ptr<dae::GameObject>& pObject, const OBSERVER_EVENTS& event)
{
	if (event == OBSERVER_EVENTS::PLAYER_DIED)
	{
		std::shared_ptr<HealthComponent> pHealthComponent = pObject->GetComponent<HealthComponent>();

		pHealthComponent->DecreaseLives(1);
		m_pMessageReceiver->GetComponent<TextComponent>()->SetHealthText(std::to_string(pHealthComponent->GetLives()));
	}
}
