#include "DemoScene.h"

#include <Observers.h>
#include <Observers.h>
#include <GameObject.h>

#include <FPSComponent.h>
#include <TextComponent.h>
#include <LevelComponent.h>
#include <ScoreComponent.h>
#include <RenderComponent.h>
#include <HealthComponent.h>
#include <TextureComponent.h>

#include <Locator.h>
#include <ResourceManager.h>

#include <memory>

Helheim::DemoScene::DemoScene()
		: Scene("DemoScene")
{}
Helheim::DemoScene::~DemoScene()
{}

void Helheim::DemoScene::Initialize()
{}
void Helheim::DemoScene::Update(const float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}
void Helheim::DemoScene::FixedUpdate(const float timeEachUpdate)
{
	UNREFERENCED_PARAMETER(timeEachUpdate);
}
void Helheim::DemoScene::LateUpdate()
{}
void Helheim::DemoScene::Render() const
{}

void Helheim::DemoScene::CreateBackground(Helheim::Scene& scene) const
{
	glm::vec3 position = glm::vec3{ 0, 0, 0 };
	glm::vec3 rotation = glm::vec3{ 0, 0, 0 };
	glm::vec3 scale    = glm::vec3{ 1, 1, 1 };

	Helheim::GameObject* pBackgroundGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::TextureComponent* pTextureComp1 = new Helheim::TextureComponent("background.jpg", pBackgroundGO);
	pBackgroundGO->AddComponent(pTextureComp1);
	scene.AddGameObject(pBackgroundGO);
}
void Helheim::DemoScene::CreateLogo(Helheim::Scene& scene) const
{
	glm::vec3 position = glm::vec3{ 216.f, 180.f, 0.f };
	glm::vec3 rotation = glm::vec3{ 0.f,   0.f, 0.f };
	glm::vec3 scale    = glm::vec3{ 1.f,   1.f, 1.f };

	Helheim::GameObject* pLogoGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::TextureComponent* pTextureComponent = new Helheim::TextureComponent("logo.png", pLogoGO);
	pLogoGO->AddComponent(pTextureComponent);
	scene.AddGameObject(pLogoGO);
}
void Helheim::DemoScene::CreateFPSCounter(Helheim::Scene& scene) const
{
	Helheim::Font* pFpsFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", 20) };

	glm::vec3 position = glm::vec3{ 280, 20, 0 };
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale    = glm::vec3{ 1,  1, 1 };

	Helheim::GameObject* pFpsGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::FPSComponent* pFPSComponent = new Helheim::FPSComponent(pFpsGO, pFpsFont);
	pFpsGO->AddComponent(pFPSComponent);
	scene.AddGameObject(pFpsGO);
}
void Helheim::DemoScene::CreateTitle(Helheim::Scene& scene) const
{
	Helheim::Font* pTitleFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", 40) };

	glm::vec3 position = glm::vec3{ 60, 75, 0 };
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale    = glm::vec3{ 1,  1, 1 };

	Helheim::GameObject* pTitleGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::TextComponent* pTextComponent = new Helheim::TextComponent(pTitleGO, "Programming 4 Assignment", pTitleFont);
	pTitleGO->AddComponent(pTextComponent);
	scene.AddGameObject(pTitleGO);
}
void Helheim::DemoScene::CreateQBERTs(Helheim::Scene& scene) const
{
	const size_t maxPlayers{ 2 };
	for (size_t i{}; i < maxPlayers; ++i)
	{
		// Health UI
		Helheim::Font* pHealthFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", 20) };
		
		glm::vec3 position = glm::vec3{ (i == 0) ? 525 : 20 , 10, 0 };
		glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
		glm::vec3 scale    = glm::vec3{ 1,  1, 1 };

		Helheim::GameObject* pQbertUIGO = new Helheim::GameObject(position, rotation, scale);
		Helheim::TextComponent* pTextComponent0 = new Helheim::TextComponent(pQbertUIGO, "Lives left: 3", pHealthFont);
		pQbertUIGO->AddComponent(pTextComponent0);
		pQbertUIGO->SetName("Health UI - P" + std::to_string(i + 1));
		scene.AddGameObject(pQbertUIGO);

		// Score UI
		Helheim::Font* pScoreFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", 20) };

		position = glm::vec3{ (i == 0) ? 525 : 20, 30, 0 };
		rotation = glm::vec3{ 0,  0, 0 };
		scale    = glm::vec3{ 1,  1, 1 };

		Helheim::GameObject* pScoreUIGO = new Helheim::GameObject(position, rotation, scale);
		Helheim::TextComponent* pTextComponent1 = new Helheim::TextComponent(pScoreUIGO, "Score: 0", pScoreFont);
		pScoreUIGO->AddComponent(pTextComponent1);
		pScoreUIGO->SetName("Score UI - P" + std::to_string(i + 1));
		scene.AddGameObject(pScoreUIGO);

		// QBERT itself
		position = glm::vec3{ 200 + (i * 100),   424,    0 };
		rotation = glm::vec3{ 0,     0,    0 };
		scale    = glm::vec3{ 0.1f,  0.1f, 0.1f };

		Helheim::GameObject* pQbertGO = new Helheim::GameObject(position, rotation, scale);
		Helheim::TextureComponent* pTextureComponent = new Helheim::TextureComponent("Qbert.png", pQbertGO);
		Helheim::HealthComponent* pHealthComponent = new Helheim::HealthComponent(pQbertGO, 10, 3);
		Helheim::ScoreComponent* pScoreComponent = new Helheim::ScoreComponent(pQbertGO);
		pQbertGO->AddComponent(pTextureComponent);
		pQbertGO->AddComponent(pHealthComponent);
		pQbertGO->AddComponent(pScoreComponent);
		pQbertGO->SetName("QBERT - P" + std::to_string(i + 1));
		scene.AddGameObject(pQbertGO);
	}

	auto player1{ scene.GetObjectByName("QBERT - P1") };
	auto player2{ scene.GetObjectByName("QBERT - P2") };
	auto healthUI_P1{ scene.GetObjectByName("Health UI - P1") };
	auto healthUI_P2{ scene.GetObjectByName("Health UI - P2") };
	std::shared_ptr<Helheim::Health> pHealthObserver = std::make_shared<Helheim::Health>(healthUI_P1, healthUI_P2);
	player1->GetComponent<HealthComponent>()->AddObserver(pHealthObserver);
	player2->GetComponent<HealthComponent>()->AddObserver(pHealthObserver);
}
void Helheim::DemoScene::CreateLEVEL(Helheim::Scene& scene) const
{
	Helheim::GameObject* player1{ scene.GetObjectByName("Score UI - P1") };
	Helheim::GameObject* player2{ scene.GetObjectByName("Score UI - P2") };

	// Level - Cube
	glm::vec3 position = glm::vec3{ 400, 200, 0 };
	glm::vec3 rotation = glm::vec3{ 0,   0, 0 };
	glm::vec3 scale    = glm::vec3{ 1,   1, 1 };

	Helheim::GameObject* pLevelGO = new Helheim::GameObject(position, rotation, scale);
	std::shared_ptr<Helheim::Score> pScoreObserver = std::make_shared<Helheim::Score>(player1, player2);
	Helheim::LevelComponent* pLevelComponent = new Helheim::LevelComponent(pLevelGO, glm::vec3(1, 0, 0));
	pLevelComponent->AddObserver(pScoreObserver);
	pLevelGO->AddComponent(pLevelComponent);
	pLevelGO->SetName("LevelCube");
	scene.AddGameObject(pLevelGO);
}