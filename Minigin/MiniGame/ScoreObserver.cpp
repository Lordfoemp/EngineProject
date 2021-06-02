#include "MiniGamePCH.h"
#include "ScoreObserver.h"

#include <iostream>

#include "GameObject.h"

#include <ScoreComponent.h>
#include <TextComponent.h>

Helheim::ScoreObserver::ScoreObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2)
					   : Observer(pMessageRecieverP1, pMessageRecieverP2)
{}
void Helheim::ScoreObserver::OnNotify(Helheim::GameObject*, const OBSERVER_EVENTS& event) // pObject - event
{
	std::cout << "Extra score jeej \n";

	if (event == OBSERVER_EVENTS::COLOR_CHANGE_P1)
	{
		ScoreComponent* pScoreComponent{ static_cast<ScoreComponent*>(m_pOwningComponent) };
		TextComponent* pTextComponent{ m_pOwningComponent->GetParentObject()->GetComponent<TextComponent>() };

		int score{ pScoreComponent->GetScore() };
		pTextComponent->SetScoreText(std::to_string(score));
	}
	else if (event == OBSERVER_EVENTS::COLOR_CHANGE_P2)
	{
		ScoreComponent* pScoreComponent{ static_cast<ScoreComponent*>(m_pOwningComponent) };
		TextComponent* pTextComponent{ m_pOwningComponent->GetParentObject()->GetComponent<TextComponent>() };

		int score{ pScoreComponent->GetScore() };
		pTextComponent->SetScoreText(std::to_string(score));
	}
}