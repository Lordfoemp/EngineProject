#include "MiniginPCH.h"
#include "FPSComponent.h"

// dae Includes
#include "GameObject.h"

// Helheim Includes
#include "Timer.h"
#include "TextComponent.h"

Helheim::FPSComponent::FPSComponent(std::shared_ptr<dae::GameObject>& pParentObject, std::shared_ptr<dae::Font> pFont)
					  : Component(pParentObject, false)
					  , m_FPS()
					  , m_FrameCounter()
					  , m_FrameTime()
{
	std::shared_ptr<Helheim::TextComponent> pTextComp = std::make_shared<Helheim::TextComponent>(pParentObject, "0", pFont);
	pParentObject->AddComponent(pTextComp);
}

void Helheim::FPSComponent::Initialize()
{}
void Helheim::FPSComponent::Update()
{
	Timer& timer{ Timer::GetInstance() };
	m_FrameCounter++;
	m_FrameTime += timer.GetMsEachUpdate();
	if (m_FrameTime >= 1)
	{
		m_FPS = m_FrameCounter;
		m_FrameCounter = 0;
		m_FrameTime = 0;

		m_pParentObject->GetComponent<Helheim::TextComponent>()->SetFPSText(std::to_string(m_FPS));
	}
}