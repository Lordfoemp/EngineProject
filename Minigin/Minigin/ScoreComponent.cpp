#include "MiniginPCH.h"
#include "ScoreComponent.h"

// dae Includes
#include "GameObject.h"

// Helheim Includes
#include "Timer.h"
#include "TextComponent.h"

Helheim::ScoreComponent::ScoreComponent(Helheim::GameObject* pParentObject)
						: Component(pParentObject, false)
						, m_Score()
{}

void Helheim::ScoreComponent::Initialize(Scene*) // pParentScene
{}
void Helheim::ScoreComponent::Update(const float)
{
	/*if (m_OldScore != m_Score)
	{
		m_pObservers[0]->OnNotify(m_pParentObject, Observer::OBSERVER_EVENTS::COLOR_CHANGE_P1);
		m_OldScore = m_Score;
	}*/
}
void Helheim::ScoreComponent::FixedUpdate(const float)
{}