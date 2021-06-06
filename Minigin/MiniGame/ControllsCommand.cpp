#include "MiniGamePCH.h"
#include "ControllsCommand.h"

void Helheim::ControllsCommand::Execute()
{
	PressControllsButton();
}

void Helheim::ControllsCommand::PressControllsButton()
{
	SceneManager* pSceneManager{ Locator::GetSceneService() };
	Scene* pScene{ pSceneManager->GetActiveMenuScene() };
	std::vector<Helheim::Scene::Button> buttons{ pScene->GetButtons() };
	Helheim::Scene::Button playButton{ buttons[1] };
	TextureComponent* pTexture{ playButton.pTextureComponent_Pressed };

	if (pTexture->CanRenderComponent())
	{
		Locator::GetSceneService()->DeactivateAllMenuScenes();
		Locator::GetSceneService()->ActivateMenuSceneByIndex(1);
	}
}