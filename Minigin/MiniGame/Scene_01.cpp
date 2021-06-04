#include "MiniGamePCH.h"
#include "Scene_01.h"

//#include "QBERT.h"
#include "Level.h"
//#include "Cube.h"

Helheim::Scene_01::Scene_01(const int windowWidth, const int windowHeight, const bool isActive)
				  : Scene(windowWidth, windowHeight, isActive)
				  , m_pLevel(nullptr)
{}

void Helheim::Scene_01::Initialize()
{
	InitializeLevel();
	Scene::Initialize();
}
void Helheim::Scene_01::Update(const float elapsedSec) //elapsedSec
{
	Scene::Update(elapsedSec);
}
void Helheim::Scene_01::FixedUpdate(const float timeEachUpdate) //timeEachUpdate
{
	Scene::FixedUpdate(timeEachUpdate);
}
void Helheim::Scene_01::LateUpdate()
{
	Scene::LateUpdate();
}
void Helheim::Scene_01::Render() const
{
	Scene::Render();
}

Helheim::Level* Helheim::Scene_01::GetLevel() const
{
	return m_pLevel;
}

void Helheim::Scene_01::InitializeLevel()
{
	m_pLevel = new Level();
	m_pLevel->Initialize(this, "QBERT/Level_01/", LevelComponent::LevelNmr::Level01);
}