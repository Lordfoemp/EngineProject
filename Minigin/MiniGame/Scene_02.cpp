#include "MiniGamePCH.h"
#include "Scene_02.h"

//#include "QBERT.h"
#include "Level.h"
//#include "Cube.h"

Helheim::Scene_02::Scene_02(const int windowWidth, const int windowHeight, const bool isActive)
				  : Scene(windowWidth, windowHeight, isActive)
				  , m_pLevel(nullptr)
{}

void Helheim::Scene_02::Initialize()
{
	InitializeLevel();
	Scene::Initialize();
}
void Helheim::Scene_02::Update(const float elapsedSec) //elapsedSec
{
	Scene::Update(elapsedSec);
}
void Helheim::Scene_02::FixedUpdate(const float timeEachUpdate) //timeEachUpdate
{
	Scene::FixedUpdate(timeEachUpdate);
}
void Helheim::Scene_02::LateUpdate()
{
	Scene::LateUpdate();
}
void Helheim::Scene_02::Render() const
{
	Scene::Render();
}

Helheim::Level* Helheim::Scene_02::GetLevel() const
{
	return m_pLevel;
}

void Helheim::Scene_02::InitializeLevel()
{
	m_pLevel = new Level();
	m_pLevel->Initialize(this, "QBERT/Level_02/");
}