#include "MiniGamePCH.h"
#include "BackCommand.h"

void Helheim::BackCommand::Execute()
{
	PressBackButton();
}

void Helheim::BackCommand::PressBackButton()
{
	SceneManager* pSceneManager{ Locator::GetSceneService() };
	Scene* pScene{ pSceneManager->GetActiveMenuScene() };
	std::vector<Helheim::Scene::Button> buttons{ pScene->GetButtons() };
	Helheim::Scene::Button playButton{ buttons[0] };
	TextureComponent* pTexture{ playButton.pTextureComponent_Pressed };

	if (pTexture->CanRenderComponent())
	{
		Locator::GetSceneService()->DeactivateAllMenuScenes();
		Locator::GetSceneService()->ActivateMenuSceneByIndex(0);
	}
}
