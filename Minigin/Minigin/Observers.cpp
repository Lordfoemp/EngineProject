#include "MiniginPCH.h"
#include "Observers.h"

// Helheim includes
#include "TextComponent.h"
#include "HealthComponent.h"
#include "LevelComponent.h"
#include "ScoreComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "SceneManager.h"
#include "Scene.h"
//#include "../MiniGame/Scene_01.h"
//#include "../MiniGame/Scene_02.h"
#include "GameObject.h"
//#include "../MiniGame/Level.h"
//#include "../MiniGame/Cube.h"

Helheim::HealthObserver::HealthObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2)
						: Observer(pMessageRecieverP1, pMessageRecieverP2)
{}
void Helheim::HealthObserver::OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event)
{
	UNREFERENCED_PARAMETER(pObject);

	//const std::shared_ptr<Helheim::Scene> activescene{ Helheim::SceneManager::GetInstance().GetActiveScene() };
	Helheim::Scene* activescene{ Locator::GetSceneService()->GetActiveScene() };

	if (event == OBSERVER_EVENTS::PLAYER_DIED_P1)
	{
		auto p1{ activescene->GetObjectByName("QBERT - P1") };
		HealthComponent* pHealthComponent = p1->GetComponent<Helheim::HealthComponent>();

		pHealthComponent->DecreaseLives(1);
		m_pMessageReceiverP1->GetComponent<TextComponent>()->SetHealthText(std::to_string(pHealthComponent->GetLives()));
	}
	else if (event == OBSERVER_EVENTS::PLAYER_DIED_P2)
	{
		auto p2{ activescene->GetObjectByName("QBERT - P2") };
		Helheim::HealthComponent* pHealthComponent = p2->GetComponent<Helheim::HealthComponent>();

		pHealthComponent->DecreaseLives(1);
		m_pMessageReceiverP2->GetComponent<TextComponent>()->SetHealthText(std::to_string(pHealthComponent->GetLives()));
	}
}

//Helheim::ScoreObserver::ScoreObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2)
//			   : Observer(pMessageRecieverP1, pMessageRecieverP2)
//			   , m_Score()
//{}
//void Helheim::ScoreObserver::OnNotify(Helheim::GameObject* , const OBSERVER_EVENTS& event)//pObject
//{
//	//const std::shared_ptr<Helheim::Scene> activescene{ Helheim::SceneManager::GetInstance().GetActiveScene() };
//	//Helheim::Scene* activescene{ Locator::GetSceneService()->GetActiveScene() };
//	if (event == OBSERVER_EVENTS::COLOR_CHANGE_P1)
//	{
//		ScoreComponent* pScoreComponent{ static_cast<ScoreComponent*>(m_pOwningComponent) };
//		TextComponent* pTextComponent{ m_pOwningComponent->GetParentObject()->GetComponent<TextComponent>() };
//
//		int score{ pScoreComponent->GetScore() }; 
//		pTextComponent->SetScoreText(std::to_string(score));
//	}
//	else if (event == OBSERVER_EVENTS::COLOR_CHANGE_P2)
//	{
//		ScoreComponent* pScoreComponent{ static_cast<ScoreComponent*>(m_pOwningComponent) };
//		TextComponent* pTextComponent{ m_pOwningComponent->GetParentObject()->GetComponent<TextComponent>() };
//
//		int score{ pScoreComponent->GetScore() };
//		pTextComponent->SetScoreText(std::to_string(score));
//	}
//}

//Helheim::LevelObserver::LevelObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2)
//	: Observer(pMessageRecieverP1, pMessageRecieverP2)
//{}
//void Helheim::LevelObserver::OnNotify(Helheim::GameObject* , const OBSERVER_EVENTS& ) // pObject - event
//{
//	std::cout << "Load next level \n";
//	/*SceneManager* pSceneManager = Locator::GetSceneService();
//	pSceneManager->ActivateNextScene();
//
//	if (pSceneManager->GetActiveSceneIndex() == 1)
//	{
//		auto cube0 = static_cast<Scene_02*>(pSceneManager->GetActiveScene())->GetLevel()->GetLevelComponent()->GetCubeByIndex(0);
//		pSceneManager->GetActiveScene()->GetObjectByName("Player 1")->GetComponent<TransformComponent>()->SetPosition(cube0->GetGameObject()->GetComponent<TransformComponent>()->GetPosition());
//	}*/
//}