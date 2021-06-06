#include "MiniGamePCH.h"
#include "CubeComponent.h"

#include "GameObject.h"
#include "TextureComponent.h"

#include "SceneManager.h"

Helheim::CubeComponent::CubeComponent(Helheim::GameObject* pParentObject)
					   : Component(pParentObject, false)
					   , m_StepCounter()
					   , m_pTextureComponent(nullptr)
					   , m_pConnections(std::vector<Connection*>())
					   , m_IsVisited(false)
{}

void Helheim::CubeComponent::Initialize(Scene* )	//pParentScene
{}
void Helheim::CubeComponent::PostInitialize(Scene* )	//pParentScene
{
	m_pTextureComponent = m_pParentObject->GetComponent<TextureComponent>();
}
void Helheim::CubeComponent::Update(const float )	//elapsedSec
{
}
void Helheim::CubeComponent::FixedUpdate(const float )	//timeEachUpdate
{
}


bool Helheim::CubeComponent::ChangeColor()
{
	if (Locator::GetSceneService()->GetActiveGameSceneIndex() == 0)
	{
		// If the first texture is being renderd activate the next one
		if (m_pTextureComponent->CanRenderComponent())
		{
			m_StepCounter++;
			m_pTextureComponent->UpdateRenderSettings(32, 32, 32);
			m_IsVisited = true;
		}
	}
	else if (Locator::GetSceneService()->GetActiveGameSceneIndex() == 1)
	{
		int leftRenderPosition{ m_pTextureComponent->GetLeftPosition() };
		// If the first texture is being renderd activate the next one
		if (m_pTextureComponent->CanRenderComponent() && leftRenderPosition == 0)
		{
			m_StepCounter++;
			m_pTextureComponent->UpdateRenderSettings(32, 32, 32);
		}
		// If the second texture is being renderd activate the next one
		if (m_pTextureComponent->CanRenderComponent() && leftRenderPosition == 32)
		{
			m_StepCounter++;
			m_pTextureComponent->UpdateRenderSettings(32, 32, 64);
			m_IsVisited = true;
		}
	}
	else if (Locator::GetSceneService()->GetActiveGameSceneIndex() == 2)
	{
		int leftRenderPosition{ m_pTextureComponent->GetLeftPosition() };
		// If the first texture is being renderd activate the next one
		if (m_pTextureComponent->CanRenderComponent() && leftRenderPosition == 0)
		{
			m_StepCounter++;
			m_pTextureComponent->UpdateRenderSettings(32, 32, 32);
			m_IsVisited = true;
		}
		// If the second texture is being renderd activate the next one
		if (m_pTextureComponent->CanRenderComponent() && leftRenderPosition == 32)
		{
			m_StepCounter--;
			m_pTextureComponent->UpdateRenderSettings(32, 32, 0);
			m_IsVisited = false;
		}
	}

	return false;
}