#include "MiniGamePCH.h"
#include "QuitCommand.h"

void Helheim::QuitCommand::Execute()
{
	PressQuitButton();
}

void Helheim::QuitCommand::PressQuitButton()
{
	SceneManager* pSceneManager{ Locator::GetSceneService() };
	Scene* pScene{ pSceneManager->GetActiveMenuScene() };
	std::vector<Helheim::Scene::Button> buttons{ pScene->GetButtons() };
	Helheim::Scene::Button playButton{ buttons[2] };
	TextureComponent* pTexture{ playButton.pTextureComponent_Pressed };

	if (pTexture->CanRenderComponent())
	{
		//Locator::GetSceneService()->DeactivateAllMenuScenes();
		//Locator::GetSceneService()->ActivateGameSceneByIndex(0);
	}
}