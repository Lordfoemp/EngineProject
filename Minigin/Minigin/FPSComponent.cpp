#include "MiniginPCH.h"
#include "FPSComponent.h"

// dae Includes
#include "GameObject.h"

// Helheim Includes
#include "Timer.h"
#include "TextComponent.h"

Helheim::FPSComponent::FPSComponent(dae::GameObject* pParentObject, std::shared_ptr<dae::Font> pFont)
					  : Component(pParentObject, false)
					  , m_FPS()
					  , m_FrameCounter()
					  , m_FrameTime()
{
	if (!pParentObject->HasComponent<Helheim::TextComponent>())
	{
		m_pTextComponent = std::make_shared<Helheim::TextComponent>(pParentObject, "0", pFont);
		pParentObject->AddComponent(m_pTextComponent);
	}
	else
		m_pTextComponent = pParentObject->GetComponent<Helheim::TextComponent>();
}

void Helheim::FPSComponent::Initialize()
{}
void Helheim::FPSComponent::Update()
{}
void Helheim::FPSComponent::FixedUpdate()
{
	Timer& timer{ Timer::GetInstance() };
	m_FrameCounter++;
	m_FrameTime += timer.GetMsEachUpdate();
	if (m_FrameTime >= 1)
	{
		m_FPS = m_FrameCounter;
		m_FrameCounter = 0;
		m_FrameTime -= 1.f;
		
		m_pTextComponent->SetFPSText(std::to_string(m_FPS));
	}
}