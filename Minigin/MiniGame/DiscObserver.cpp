#include "MiniGamePCH.h"
#include "DiscObserver.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "QBERTComponent.h"
#include "TransformComponent.h"
#include "JumpComponent.h"
#include "LevelComponent.h"
#include "DiscComponent.h"

#include "SceneManager.h"
#include "Scene.h"

Helheim::DiscObserver::DiscObserver()
	: Observer()
{}

void Helheim::DiscObserver::OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS & event)
{
	if (event == OBSERVER_EVENTS::DELETE_DISC)
	{
		// Stop rendering the disc (= bye bye from view)
		pObject->GetComponent<TextureComponent>()->SetCanRenderComponent(false);

		// Reset player so it starts from the top 
		GameObject* pPlayerGO{ Locator::GetSceneService()->GetActiveGameScene()->GetObjectByName("Player 1") };
		pPlayerGO->GetComponent<QBERTComponent>()->Reset(pObject->GetComponent<TransformComponent>()->GetPosition());
	}
}