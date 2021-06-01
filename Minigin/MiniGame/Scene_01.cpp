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
#include "Cube.h"

// GLM Includes
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

Helheim::Scene_01::Scene_01(const int windowWidth, const int windowHeight)
				  : Scene(windowWidth, windowHeight)
				  , m_pLevelComponent(nullptr)
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

void Helheim::Scene_01::InitializeLevel()
{
	//Helheim::GameObject* player1{ GetObjectByName("Score UI - P1") };
	//Helheim::GameObject* player2{ GetObjectByName("Score UI - P2") };

	// Level - Cube
	glm::vec3 position = glm::vec3{ 400, 200, 0 };
	glm::vec3 rotation = glm::vec3{ 0,   0, 0 };
	glm::vec3 scale = glm::vec3{ 1,   1, 1 };

	m_pLevelGO = new Helheim::GameObject(position, rotation, scale);
	//std::shared_ptr<Helheim::Score> pScoreObserver = std::make_shared<Helheim::Score>(player1, player2);
	m_pLevelComponent = new Helheim::LevelComponent(m_pLevelGO, glm::vec3(1, 0, 0));
	//pLevelComponent->AddObserver(pScoreObserver);
	m_pLevelGO->AddComponent(m_pLevelComponent);
	m_pLevelGO->SetName("LevelCube");
	AddGameObject(m_pLevelGO);
}
void Helheim::Scene_01::InitializeQBERT()
{
	m_pQBERT = new QBERT("Player 1");
	m_pQBERT->Initialize(this, {640/2 - 17.5f, 60, 10});
}