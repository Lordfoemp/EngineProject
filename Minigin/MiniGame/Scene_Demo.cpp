#include "MiniGamePCH.h"
#include "Scene_Demo.h"

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

// GLM Includes
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

Helheim::Scene_Demo::Scene_Demo(const int windowWidth, const int windowHeight)
		: Scene(windowWidth, windowHeight)
{}

void Helheim::Scene_Demo::Initialize()
{
	CreateBackground();
	CreateLogo();
	CreateFPSCounter();
	CreateTitle();
	CreateQBERTs();
	//CreateLEVEL();
}
void Helheim::Scene_Demo::Update(const float elapsedSec)//elapsedSec
{
	Scene::Update(elapsedSec);
}
void Helheim::Scene_Demo::FixedUpdate(const float timeEachUpdate)//timeEachUpdate
{
	Scene::FixedUpdate(timeEachUpdate);
}
void Helheim::Scene_Demo::LateUpdate()
{
	Scene::LateUpdate();
}
void Helheim::Scene_Demo::Render() const
{
	Scene::Render();
}

void Helheim::Scene_Demo::CreateBackground()
{
	glm::vec3 position = glm::vec3{ 0, 0, 0 };
	glm::vec3 rotation = glm::vec3{ 0, 0, 0 };
	glm::vec3 scale = glm::vec3{ 1, 1, 1 };

	Helheim::GameObject* pBackgroundGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::TextureComponent* pTextureComp1 = new Helheim::TextureComponent("background.jpg", "Demo/", pBackgroundGO);
	pBackgroundGO->AddComponent(pTextureComp1);
	AddGameObject(pBackgroundGO);
}
void Helheim::Scene_Demo::CreateLogo()
{
	glm::vec3 position = glm::vec3{ 216.f, 180.f, 0.f };
	glm::vec3 rotation = glm::vec3{ 0.f,   0.f, 0.f };
	glm::vec3 scale = glm::vec3{ 1.f,   1.f, 1.f };

	Helheim::GameObject* pLogoGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::TextureComponent* pTextureComponent = new Helheim::TextureComponent("logo.png", "Demo/", pLogoGO);
	pLogoGO->AddComponent(pTextureComponent);
	AddGameObject(pLogoGO);
}
void Helheim::Scene_Demo::CreateFPSCounter()
{
	Helheim::Font* pFpsFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", "", 20) };

	glm::vec3 position = glm::vec3{ 280, 20, 0 };
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale = glm::vec3{ 1,  1, 1 };

	Helheim::GameObject* pFpsGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::FPSComponent* pFPSComponent = new Helheim::FPSComponent(pFpsGO, pFpsFont);
	pFpsGO->AddComponent(pFPSComponent);
	AddGameObject(pFpsGO);
}
void Helheim::Scene_Demo::CreateTitle()
{
	Helheim::Font* pTitleFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", "", 40) };

	glm::vec3 position = glm::vec3{ 60, 75, 0 };
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale = glm::vec3{ 1,  1, 1 };

	Helheim::GameObject* pTitleGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::TextComponent* pTextComponent = new Helheim::TextComponent(pTitleGO, "Programming 4 Assignment", pTitleFont);
	pTitleGO->AddComponent(pTextComponent);
	AddGameObject(pTitleGO);
}
void Helheim::Scene_Demo::CreateQBERTs()
{
	const size_t maxPlayers{ 2 };
	for (size_t i{}; i < maxPlayers; ++i)
	{
		// Health UI
		Helheim::Font* pHealthFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", "", 20) };

		glm::vec3 position = glm::vec3{ (i == 0) ? 525 : 20 , 10, 0 };
		glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
		glm::vec3 scale = glm::vec3{ 1,  1, 1 };

		Helheim::GameObject* pQbertUIGO = new Helheim::GameObject(position, rotation, scale);
		Helheim::TextComponent* pTextComponent0 = new Helheim::TextComponent(pQbertUIGO, "Lives left: 3", pHealthFont);
		pQbertUIGO->AddComponent(pTextComponent0);
		pQbertUIGO->SetName("Health UI - P" + std::to_string(i + 1));
		AddGameObject(pQbertUIGO);

		// Score UI
		Helheim::Font* pScoreFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", "", 20) };

		position = glm::vec3{ (i == 0) ? 525 : 20, 30, 0 };
		rotation = glm::vec3{ 0,  0, 0 };
		scale = glm::vec3{ 1,  1, 1 };

		Helheim::GameObject* pScoreUIGO = new Helheim::GameObject(position, rotation, scale);
		Helheim::TextComponent* pTextComponent1 = new Helheim::TextComponent(pScoreUIGO, "Score: 0", pScoreFont);
		pScoreUIGO->AddComponent(pTextComponent1);
		pScoreUIGO->SetName("Score UI - P" + std::to_string(i + 1));
		AddGameObject(pScoreUIGO);

		// QBERT itself
		position = glm::vec3{ 200 + (i * 100),   424,    0 };
		rotation = glm::vec3{ 0,     0,    0 };
		scale = glm::vec3{ 0.1f,  0.1f, 0.1f };

		Helheim::GameObject* pQbertGO = new Helheim::GameObject(position, rotation, scale);
		Helheim::TextureComponent* pTextureComponent = new Helheim::TextureComponent("Qbert.png", "QBERT/", pQbertGO);
		Helheim::HealthComponent* pHealthComponent = new Helheim::HealthComponent(pQbertGO, 10, 3);
		Helheim::ScoreComponent* pScoreComponent = new Helheim::ScoreComponent(pQbertGO);
		pQbertGO->AddComponent(pTextureComponent);
		pQbertGO->AddComponent(pHealthComponent);
		pQbertGO->AddComponent(pScoreComponent);
		pQbertGO->SetName("QBERT - P" + std::to_string(i + 1));
		AddGameObject(pQbertGO);
	}

	auto player1{ GetObjectByName("QBERT - P1") };
	auto player2{ GetObjectByName("QBERT - P2") };
	auto healthUI_P1{ GetObjectByName("Health UI - P1") };
	auto healthUI_P2{ GetObjectByName("Health UI - P2") };
	std::shared_ptr<Helheim::Health> pHealthObserver = std::make_shared<Helheim::Health>(healthUI_P1, healthUI_P2);
	player1->GetComponent<HealthComponent>()->AddObserver(pHealthObserver);
	player2->GetComponent<HealthComponent>()->AddObserver(pHealthObserver);
}
void Helheim::Scene_Demo::CreateLEVEL()
{
	Helheim::GameObject* player1{ GetObjectByName("Score UI - P1") };
	Helheim::GameObject* player2{ GetObjectByName("Score UI - P2") };

	// Level - Cube
	glm::vec3 position = glm::vec3{ 400, 200, 0 };
	glm::vec3 rotation = glm::vec3{ 0,   0, 0 };
	glm::vec3 scale = glm::vec3{ 1,   1, 1 };

	Helheim::GameObject* pLevelGO = new Helheim::GameObject(position, rotation, scale);
	std::shared_ptr<Helheim::Score> pScoreObserver = std::make_shared<Helheim::Score>(player1, player2);
	Helheim::LevelComponent* pLevelComponent = new Helheim::LevelComponent(pLevelGO, glm::vec3(1, 0, 0));
	pLevelComponent->AddObserver(pScoreObserver);
	pLevelGO->AddComponent(pLevelComponent);
	pLevelGO->SetName("LevelCube");
	AddGameObject(pLevelGO);
}