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
{}
void Helheim::ScoreComponent::FixedUpdate(const float)
{}