#include "MiniGamePCH.h"
#include "LevelObserver.h"

#include <iostream>

#include "Locator.h"
#include "SceneManager.h"
#include "Scene_01.h"
#include "Scene_02.h"
#include "Scene_03.h"
#include "Level.h"
#include "Cube.h"
#include "GameObject.h"
#include "QBERT.h"

#include <TransformComponent.h>
#include <LevelComponent.h>

Helheim::LevelObserver::LevelObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2)
					   : Observer(pMessageRecieverP1, pMessageRecieverP2)
{}
void Helheim::LevelObserver::OnNotify(Helheim::GameObject*, const OBSERVER_EVENTS& event) // pObject - event
{
	if (event == OBSERVER_EVENTS::LOAD_NEXT_LEVEL)
	{
		std::cout << "Load next level \n";
		SceneManager* pSceneManager = Locator::GetSceneService();
		pSceneManager->ActivateNextScene();

		// Retrieve the current scene
		Scene* pActiveScene{ pSceneManager->GetActiveScene() };

		// Retrieve the start cube (Index 0 in the cube list)
		Cube* pCube0{ nullptr };

		if (pSceneManager->GetActiveSceneIndex() == 1)
		{
			// Retrieve the start cube (Index 0 in the cube list)
			pCube0 = static_cast<Scene_02*>(pActiveScene)->GetLevel()->GetLevelComponent()->GetCubeByIndex(0);
		}
		if (pSceneManager->GetActiveSceneIndex() == 2)
		{
			// Retrieve the start cube (Index 0 in the cube list)
			pCube0 = static_cast<Scene_03*>(pActiveScene)->GetLevel()->GetLevelComponent()->GetCubeByIndex(0);
		}

		// Retrieve the position of the cube
		TransformComponent* pTransformComponent{ pCube0->GetGameObject()->GetComponent<TransformComponent>() };
		glm::vec3 cubePosition{ pTransformComponent->GetPosition() };

		// Reset Qbert
		QBERT* pQBERT{ pActiveScene->GetQBERT() };
		pQBERT->Reset(cubePosition);
	}

	if (event == OBSERVER_EVENTS::GAME_DONE)
	{

	}
}