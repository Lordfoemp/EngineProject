#include "MiniginPCH.h"
#include "ScoreComponent.h"

Helheim::ScoreComponent::ScoreComponent(Helheim::GameObject* pParentObject)
						: Component(pParentObject, false)
						, m_Score()
						, m_OldScore()
{
	
}

void Helheim::ScoreComponent::Initialize(Scene*) // pParentScene
{}
void Helheim::ScoreComponent::Update(const float)
{
	//std::cout << "Kakkaaa\n";
	if (m_OldScore != m_Score)
	{
		m_pObservers[0]->OnNotify(m_pParentObject, Observer::OBSERVER_EVENTS::COLOR_CHANGE_P1);
		m_OldScore = m_Score;
	}
}
void Helheim::ScoreComponent::FixedUpdate(const float)
{}