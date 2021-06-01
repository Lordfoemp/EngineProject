#include "MiniGamePCH.h"
#include "Scene_01.h"

#include "Scene.h"
#include "Audio.h"
#include "Timer.h"
#include "Renderer.h"
#include "Observers.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ThreadManager.h"
#include "ResourceManager.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "LevelComponent.h"
#include "ScoreComponent.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

#include "QBERT.h"
#include "Level.h"
#include "Cube.h"

// GLM Includes
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

Helheim::Scene_01::Scene_01(const int windowWidth, const int windowHeight)
				  : Scene(windowWidth, windowHeight)
				  , m_pLevel(nullptr)
				  , m_pQBERT(nullptr)
{}

void Helheim::Scene_01::Initialize()
{
	InitializeLevel();
	Scene::Initialize();
	InitializeQBERT();
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

Helheim::GameObject* Helheim::Scene_01::GetLevelGO() const
{
	return m_pLevel->GetGameObject();
}

void Helheim::Scene_01::InitializeLevel()
{
	m_pLevel = new Level();
	m_pLevel->Initialize(this);
}
void Helheim::Scene_01::InitializeQBERT()
{
	m_pQBERT = new QBERT("Player 1");
	m_pQBERT->Initialize(this, {640/2 - 17.5f, 60, 10});
}