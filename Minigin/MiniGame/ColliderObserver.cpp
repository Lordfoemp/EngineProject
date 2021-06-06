#include "MiniGamePCH.h"
#include "ColliderObserver.h"

#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

#include "CubeComponent.h"
#include "JumpComponent.h"
#include "LevelComponent.h"
#include "ScoreComponent.h"
#include "ColliderComponent.h"
#include "DiscComponent.h"

Helheim::ColliderObserver::ColliderObserver()
		: Observer()
{}

void Helheim::ColliderObserver::OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event)
{
	if (event == OBSERVER_EVENTS::COLOR_CUBE)
	{
		size_t cubeIndex = pObject->GetComponent<ColliderComponent>()->GetTargetCubeIndex();

		// Coloring Cube
		GameObject* pLevelGO = Locator::GetSceneService()->GetActiveGameScene()->GetObjectByName("Level");
		GameObject* pTargetCube = pLevelGO->GetComponent<LevelComponent>()->GetCubeByIndex(cubeIndex);
		CubeComponent* pCubeComponent = pTargetCube->GetComponent<CubeComponent>();
		
		// Add score because of coloring ze cube
		GameObject* pScoreGO = Locator::GetSceneService()->GetActiveGameScene()->GetObjectByName("Score UI");

		if (!pCubeComponent->GetIsVisited())
		{
			pCubeComponent->ChangeColor();
			pScoreGO->GetComponent<ScoreComponent>()->IncreaseScore(int(event));
		}
	}
	else if (event == OBSERVER_EVENTS::ACTIVATE_DISC)
	{
		// Get the current disc that needs to get activated
		JumpComponent* pJumpComponent = pObject->GetComponent<JumpComponent>();
		size_t currentDiscIdx = pJumpComponent->GetCurrentDiscIndex();

		// Activate the correct disc
		SceneManager* pSceneManager = Locator::GetSceneService();
		Scene* pScene = pSceneManager->GetActiveGameScene();
		GameObject* pLevelGO = pScene->GetObjectByName("Level");
		LevelComponent* pLevelComponent = pLevelGO->GetComponent<LevelComponent>();
		GameObject* pTargetDisc = pLevelComponent->GetDiscByIndex(currentDiscIdx);
		pTargetDisc->GetComponent<DiscComponent>()->Activate();
	}
}