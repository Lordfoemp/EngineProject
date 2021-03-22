#include "MiniginPCH.h"
#include "Observers.h"

// Helheim includes
#include "TextComponent.h"
#include "HealthComponent.h"
#include "LevelComponent.h"
#include "ScoreComponent.h"
#include "GameObject.h"

#include "SceneManager.h"
#include "Scene.h"

Helheim::Health::Health(const std::shared_ptr<Helheim::GameObject>& pMessageRecieverP1, const std::shared_ptr<Helheim::GameObject>& pMessageRecieverP2)
				: Observer(pMessageRecieverP1, pMessageRecieverP2)
{}
void Helheim::Health::OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event)
{
	UNREFERENCED_PARAMETER(pObject);

	//const std::shared_ptr<Helheim::Scene> activescene{ Helheim::SceneManager::GetInstance().GetActiveScene() };
	const std::shared_ptr<Helheim::Scene> activescene{ Locator::GetSceneService()->GetActiveScene() };

	if (event == OBSERVER_EVENTS::PLAYER_DIED_P1)
	{
		auto p1{ activescene->GetObjectByName("QBERT - P1") };
		std::shared_ptr<HealthComponent> pHealthComponent = p1->GetComponent<HealthComponent>();

		pHealthComponent->DecreaseLives(1);
		m_pMessageReceiverP1->GetComponent<TextComponent>()->SetHealthText(std::to_string(pHealthComponent->GetLives()));
	}
	else if (event == OBSERVER_EVENTS::PLAYER_DIED_P2)
	{
		auto p2{ activescene->GetObjectByName("QBERT - P2") };
		std::shared_ptr<HealthComponent> pHealthComponent = p2->GetComponent<HealthComponent>();

		pHealthComponent->DecreaseLives(1);
		m_pMessageReceiverP2->GetComponent<TextComponent>()->SetHealthText(std::to_string(pHealthComponent->GetLives()));
	}
}

Helheim::Score::Score(const std::shared_ptr<Helheim::GameObject>& pMessageRecieverP1, const std::shared_ptr<Helheim::GameObject>& pMessageRecieverP2)
			   : Observer(pMessageRecieverP1, pMessageRecieverP2)
			   , m_Score()
{}
void Helheim::Score::OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event)
{
	//const std::shared_ptr<Helheim::Scene> activescene{ Helheim::SceneManager::GetInstance().GetActiveScene() };
	const std::shared_ptr<Helheim::Scene> activescene{ Locator::GetSceneService()->GetActiveScene() };
	if (event == OBSERVER_EVENTS::COLOR_CHANGE_P1)
	{
		auto p1{ activescene->GetObjectByName("QBERT - P1") };
		auto scoreComp{ p1->GetComponent<ScoreComponent>() };
		scoreComp->IncreaseScore(25);
		int score{ scoreComp->GetScore() };
		m_pMessageReceiverP1->GetComponent<TextComponent>()->SetScoreText(std::to_string(score));
	}
	else if (event == OBSERVER_EVENTS::COLOR_CHANGE_P2)
	{
		auto p2{ activescene->GetObjectByName("QBERT - P2") };
		auto scoreComp{ p2->GetComponent<ScoreComponent>() };
		scoreComp->IncreaseScore(25);
		int score{ scoreComp->GetScore() };
		m_pMessageReceiverP2->GetComponent<TextComponent>()->SetScoreText(std::to_string(score));
	}

	// Delete
	pObject->GetComponent<LevelComponent>()->ResetChange();
}