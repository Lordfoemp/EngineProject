#include "MiniGamePCH.h"
#include "Scene_03.h"

#include "Level.h"

Helheim::Scene_03::Scene_03(const int windowWidth, const int windowHeight, const bool isActive)
	: Scene(windowWidth, windowHeight, isActive)
	, m_pLevel(nullptr)
{}
Helheim::Scene_03::~Scene_03()
{
	DELETE_POINTER(m_pLevel);
}

void Helheim::Scene_03::Initialize()
{
	InitializeLevel();
	Scene::Initialize();
}
void Helheim::Scene_03::Update(const float elapsedSec) //elapsedSec
{
	Scene::Update(elapsedSec);
}
void Helheim::Scene_03::FixedUpdate(const float timeEachUpdate) //timeEachUpdate
{
	Scene::FixedUpdate(timeEachUpdate);
}
void Helheim::Scene_03::LateUpdate()
{
	Scene::LateUpdate();
}
void Helheim::Scene_03::Render() const
{
	Scene::Render();
}

Helheim::Level* Helheim::Scene_03::GetLevel() const
{
	return m_pLevel;
}

void Helheim::Scene_03::InitializeLevel()
{
	m_pLevel = new Level();
	m_pLevel->Initialize(this, "QBERT/Level_03/", LevelComponent::LevelNmr::Level03);
}