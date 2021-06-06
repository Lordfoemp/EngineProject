#include "MiniGamePCH.h"
#include "PlayCommand.h"

void Helheim::PlayCommand::Execute()
{
	PressPlayButton();
}

void Helheim::PlayCommand::PressPlayButton()
{
	SceneManager* pSceneManager{ Locator::GetSceneService() };
	Scene* pScene{ pSceneManager->GetActiveMenuScene() };
	std::vector<Helheim::Scene::Button> buttons{ pScene->GetButtons() };
	Helheim::Scene::Button playButton{ buttons[0] };
	TextureComponent* pTexture{ playButton.pTextureComponent_Pressed };

	if (pTexture->CanRenderComponent())
	{
		Locator::GetSceneService()->DeactivateAllMenuScenes();
		Locator::GetSceneService()->ActivateGameSceneByIndex(0);
	}
}