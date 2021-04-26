#include "MiniginPCH.h"
#include "Minigin.h"

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

#include <SDL.h>

void Helheim::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	m_pWindow = SDL_CreateWindow( "Programming 4 assignment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL );
	if (!m_pWindow)
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		throw std::runtime_error(std::string("Mix_OpenAudio Error: ") + Mix_GetError());

	InitializeLocator();
	InitializeSounds();
}

/**
 * Code constructing the scene world starts here
 */
void Helheim::Minigin::LoadGame() const
{
	Helheim::Scene& scene = Locator::GetSceneService()->CreateScene("Demo");

	CreateBackground(scene);
	CreateLogo(scene);
	CreateFPSCounter(scene);
	CreateTitle(scene);
	CreateQBERTs(scene);
	CreateLEVEL(scene);
}

void Helheim::Minigin::Cleanup()
{
	DELETE_POINTER(m_pRenderer);
	DELETE_POINTER(m_pConsoleAudio);
	DELETE_POINTER(m_pLoggingAudio);
	DELETE_POINTER(m_pSceneManager);
	DELETE_POINTER(m_pInputManager);
	DELETE_POINTER(m_pThreadManager);
	DELETE_POINTER(m_pResourceManager);

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void Helheim::Minigin::Run()
{
	{
		Helheim::Timer* pTimer{ new Timer() };
		
		bool doContinue{ true };
		const float timeEachUpdate{ pTimer->GetMsEachUpdate() };
		while (doContinue)
		{
			const float elapsedSec{ pTimer->GetElapsedTime() };
			
			doContinue = m_pInputManager->ProcessInput(elapsedSec);
			pTimer->Update();

			//Fixed Update
			while (pTimer->GetLag() >= timeEachUpdate)
			{
				m_pSceneManager->FixedUpdate(timeEachUpdate);
				pTimer->SubtractFixedUpdateFromLag();
			}
			m_pSceneManager->Update(elapsedSec);
			m_pSceneManager->Render();
		}

		DELETE_POINTER(pTimer);
	}

	Cleanup();
}

void Helheim::Minigin::InitializeLocator()
{
	// Resource
	m_pResourceManager = { new ResourceManager() };
	m_pResourceManager->Init("../Data/");
	Locator::ProvideResourceService(m_pResourceManager);

	// Input
	m_pInputManager = { new InputManager() };
	Locator::ProvideInputService(m_pInputManager);

	// Scene
	m_pSceneManager = { new SceneManager() };
	Locator::ProvideSceneService(m_pSceneManager);

	// Thread
	m_pThreadManager = { new ThreadManager() };
	Locator::ProvideThreadService(m_pThreadManager);

	// Audio services
	m_pConsoleAudio = { new ConsoleAudio() };
	Locator::ProvideAudioService(m_pConsoleAudio);
	m_pLoggingAudio = Locator::EnableAudioLogging();

	// Renderer
	m_pRenderer = { new Renderer() };
	m_pRenderer->Init(m_pWindow);
	Locator::ProvideRendererService(m_pRenderer);
}
void Helheim::Minigin::InitializeSounds()
{
	// When adding sounds, dont forget to add the message with the needed value in the enum class in "Events.h"
	m_pConsoleAudio->AddSound("drumloop", AudioMessages::PLAYER_DIED);
	m_pConsoleAudio->AddSound("shouting_1_meghan", AudioMessages::SCORE_UP);
}

void Helheim::Minigin::CreateBackground(Helheim::Scene& scene) const
{
	glm::vec3 position = glm::vec3{ 0, 0, 0 };
	glm::vec3 rotation = glm::vec3{ 0, 0, 0 };
	glm::vec3 scale    = glm::vec3{ 1, 1, 1 };

	Helheim::GameObject* pBackgroundGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::TextureComponent* pTextureComp1 = new Helheim::TextureComponent("background.jpg", pBackgroundGO);
	pBackgroundGO->AddComponent(pTextureComp1);
	scene.Add(pBackgroundGO);
}
void Helheim::Minigin::CreateLogo(Helheim::Scene& scene) const
{
	glm::vec3 position = glm::vec3{ 216.f, 180.f, 0.f };
	glm::vec3 rotation = glm::vec3{ 0.f,   0.f, 0.f };
	glm::vec3 scale    = glm::vec3{ 1.f,   1.f, 1.f };

	Helheim::GameObject* pLogoGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::TextureComponent* pTextureComponent = new Helheim::TextureComponent("logo.png", pLogoGO);
	pLogoGO->AddComponent(pTextureComponent);
	scene.Add(pLogoGO);
}
void Helheim::Minigin::CreateFPSCounter(Helheim::Scene& scene) const
{
	Helheim::Font* pFpsFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", 20) };

	glm::vec3 position = glm::vec3{ 280, 20, 0 };
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale    = glm::vec3{ 1,  1, 1 };

	Helheim::GameObject* pFpsGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::FPSComponent* pFPSComponent = new Helheim::FPSComponent(pFpsGO, pFpsFont);
	pFpsGO->AddComponent(pFPSComponent);
	scene.Add(pFpsGO);
}
void Helheim::Minigin::CreateTitle(Helheim::Scene& scene) const
{
	Helheim::Font* pTitleFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", 40) };

	glm::vec3 position = glm::vec3{ 60, 75, 0 };
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale    = glm::vec3{ 1,  1, 1 };

	Helheim::GameObject* pTitleGO = new Helheim::GameObject(position, rotation, scale);
	Helheim::TextComponent* pTextComponent = new Helheim::TextComponent(pTitleGO, "Programming 4 Assignment", pTitleFont);
	pTitleGO->AddComponent(pTextComponent);
	scene.Add(pTitleGO);
}
void Helheim::Minigin::CreateQBERTs(Helheim::Scene& scene) const
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
		scene.Add(pQbertUIGO);

		// Score UI
		Helheim::Font* pScoreFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", 20) };

		position = glm::vec3{ (i == 0) ? 525 : 20, 30, 0 };
		rotation = glm::vec3{ 0,  0, 0 };
		scale    = glm::vec3{ 1,  1, 1 };

		Helheim::GameObject* pScoreUIGO = new Helheim::GameObject(position, rotation, scale);
		Helheim::TextComponent* pTextComponent1 = new Helheim::TextComponent(pScoreUIGO, "Score: 0", pScoreFont);
		pScoreUIGO->AddComponent(pTextComponent1);
		pScoreUIGO->SetName("Score UI - P" + std::to_string(i + 1));
		scene.Add(pScoreUIGO);

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
		scene.Add(pQbertGO);
	}

	auto player1{ scene.GetObjectByName("QBERT - P1") };
	auto player2{ scene.GetObjectByName("QBERT - P2") };
	auto healthUI_P1{ scene.GetObjectByName("Health UI - P1") };
	auto healthUI_P2{ scene.GetObjectByName("Health UI - P2") };
	std::shared_ptr<Helheim::Health> pHealthObserver = std::make_shared<Helheim::Health>(healthUI_P1, healthUI_P2);
	player1->GetComponent<HealthComponent>()->AddObserver(pHealthObserver);
	player2->GetComponent<HealthComponent>()->AddObserver(pHealthObserver);
}
void Helheim::Minigin::CreateLEVEL(Helheim::Scene& scene) const
{
	UNREFERENCED_PARAMETER(scene);

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
	scene.Add(pLevelGO);
}