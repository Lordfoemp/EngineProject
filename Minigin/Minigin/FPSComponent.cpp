#include "MiniginPCH.h"
#include "FPSComponent.h"

// dae Includes
#include "GameObject.h"

// Helheim Includes
#include "Timer.h"
#include "TextComponent.h"

Helheim::FPSComponent::FPSComponent(Helheim::GameObject* pParentObject, Font* pFont)
					  : Component(pParentObject, false)
					  , m_FPS()
					  , m_FrameCounter()
					  , m_FrameTime()
{
	if (!pParentObject->HasComponent<Helheim::TextComponent>())
	{
		m_pTextComponent = new Helheim::TextComponent(pParentObject, "0", pFont);
		pParentObject->AddComponent(m_pTextComponent);
	}
	else
		m_pTextComponent = pParentObject->GetComponent<Helheim::TextComponent>();
}

void Helheim::FPSComponent::Initialize(Scene* ) // pParentScene
{}
void Helheim::FPSComponent::PostInitialize(Scene*)//pParentScene
{
}
void Helheim::FPSComponent::Update(const float)
{}
void Helheim::FPSComponent::FixedUpdate(const float timeEachUpdate)
{
	m_FrameCounter++;
	m_FrameTime += timeEachUpdate;
	if (m_FrameTime >= 1)
	{
		m_FPS = m_FrameCounter;
		m_FrameCounter = 0;
		m_FrameTime -= 1.f;
		
		m_pTextComponent->SetFPSText(std::to_string(m_FPS));
	}
}