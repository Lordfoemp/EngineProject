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

void Helheim::ScoreComponent::Initialize()
{}
void Helheim::ScoreComponent::Update()
{}
void Helheim::ScoreComponent::FixedUpdate()
{}