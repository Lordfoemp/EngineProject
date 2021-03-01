#include "MiniginPCH.h"
#include "Minigin.h"

// dae Includes
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

// Helheim Includes
#include "Timer.h"
#include "Observers.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "HealthComponent.h"
#include "LevelComponent.h"
#include "ScoreComponent.h"

using namespace std;
using namespace std::chrono;

void Helheim::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	m_pWindow = SDL_CreateWindow("Programming 4 assignment", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	if (!m_pWindow) 
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	dae::Renderer::GetInstance().Init(m_pWindow);

	InitializeConsole();
}

/**
 * Code constructing the scene world starts here
 */
void Helheim::Minigin::LoadGame() const
{
	dae::Scene& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	
	CreateBackground(scene);
	CreateLogo(scene);
	CreateFPSCounter(scene);
	CreateTitle(scene);
	CreateQBERTs(scene);	
	CreateLEVEL(scene);
}

void Helheim::Minigin::Cleanup()
{
	//dae::SceneManager::GetInstance().~SceneManager();
	dae::Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void Helheim::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& sceneManager = dae::SceneManager::GetInstance();
		auto& input = dae::InputManager::GetInstance();
		auto& timer = Helheim::Timer::GetInstance();

		bool doContinue = true;
		const float timeEachUpdate{ timer.GetMsEachUpdate() };
		while (doContinue)
		{
			timer.Update();
			doContinue = input.ProcessInput();

			//Fixed Update
			while (timer.GetLag() >= timeEachUpdate)
			{
				sceneManager.Update();
				timer.SubtractFixedUpdateFromLag();
			}

			sceneManager.Render();
		}
	}

	Cleanup();
}

void Helheim::Minigin::InitializeConsole()
{
	#ifdef _DEBUG
	// ------------------------------------
	// Code from: Overlord Engine 
	// During Graphics Programming 2 - DAE
	// Author: Matthieu Delaere
	// ------------------------------------
	if (AllocConsole())
	{
		// Redirect the CRT standard input, output, and error handles to the console
		FILE* pCout;
		freopen_s(&pCout, "CONIN$", "r", stdin);
		freopen_s(&pCout, "CONOUT$", "w", stdout);
		freopen_s(&pCout, "CONOUT$", "w", stderr);

		//Clear the error state for each of the C++ standard stream objects. We need to do this, as
		//attempts to access the standard streams before they refer to a valid target will cause the
		//iostream objects to enter an error state. In versions of Visual Studio after 2005, this seems
		//to always occur during startup regardless of whether anything has been read from or written to
		//the console or not.
		std::wcout.clear();
		std::cout.clear();
		std::wcerr.clear();
		std::cerr.clear();
		std::wcin.clear();
		std::cin.clear();
		std::cin.clear();

		//Disable Close-Button
		HWND hwnd = GetConsoleWindow();
		if (hwnd != NULL)
		{
			HMENU hMenu = GetSystemMenu(hwnd, FALSE);
			if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
		}
	}
	#endif
}

void Helheim::Minigin::CreateBackground(dae::Scene& scene) const
{
	glm::vec3 position = glm::vec3{ 0, 0, 0 };
	glm::vec3 rotation = glm::vec3{ 0, 0, 0 };
	glm::vec3 scale    = glm::vec3{ 1, 1, 1 };
	
	std::shared_ptr<dae::GameObject> pBackgroundGO = std::make_shared<dae::GameObject>(position, rotation, scale);
	std::shared_ptr<Helheim::TextureComponent> pTextureComp1 = std::make_shared<Helheim::TextureComponent>("background.jpg", pBackgroundGO.get());
	pBackgroundGO->AddComponent(pTextureComp1);
	scene.Add(pBackgroundGO);
}
void Helheim::Minigin::CreateLogo(dae::Scene& scene) const
{
	glm::vec3 position = glm::vec3{ 216.f, 180.f, 0.f };
	glm::vec3 rotation = glm::vec3{   0.f,   0.f, 0.f };
	glm::vec3 scale    = glm::vec3{   1.f,   1.f, 1.f };
	
	std::shared_ptr<dae::GameObject> pLogoGO = std::make_shared<dae::GameObject>(position, rotation, scale);
	std::shared_ptr<Helheim::TextureComponent> pTextureComponent = std::make_shared<Helheim::TextureComponent>("logo.png", pLogoGO.get());
	pLogoGO->AddComponent(pTextureComponent);
	scene.Add(pLogoGO);
}
void Helheim::Minigin::CreateFPSCounter(dae::Scene& scene) const
{
	std::shared_ptr<dae::Font> pFpsFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };
	
	glm::vec3 position = glm::vec3{ 280, 20, 0 };
	glm::vec3 rotation = glm::vec3{  0,  0, 0 };
	glm::vec3 scale    = glm::vec3{  1,  1, 1 };
	std::shared_ptr<dae::GameObject> pFpsGO = std::make_shared<dae::GameObject>(position, rotation, scale);
	std::shared_ptr<Helheim::FPSComponent> pFPSComponent = std::make_shared<Helheim::FPSComponent>(pFpsGO.get(), pFpsFont);
	pFpsGO->AddComponent(pFPSComponent);
	scene.Add(pFpsGO);
}
void Helheim::Minigin::CreateTitle(dae::Scene& scene) const
{
	std::shared_ptr<dae::Font> pTitleFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 40) };
	
	glm::vec3 position = glm::vec3{ 60, 75, 0 };
	glm::vec3 rotation = glm::vec3{  0,  0, 0 };
	glm::vec3 scale    = glm::vec3{  1,  1, 1 };
	std::shared_ptr<dae::GameObject> pTitleGO = std::make_shared<dae::GameObject>(position, rotation, scale);
	std::shared_ptr<Helheim::TextComponent> pTextComponent = std::make_shared<Helheim::TextComponent>(pTitleGO.get(), "Programming 4 Assignment", pTitleFont);
	pTitleGO->AddComponent(pTextComponent);
	scene.Add(pTitleGO);
}
void Helheim::Minigin::CreateQBERTs(dae::Scene& scene) const
{
	std::shared_ptr<dae::Font> pHealthFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };
		
	const size_t maxPlayers{ 2 };
	for (size_t i{}; i < maxPlayers; ++i)
	{
		// Health UI
		glm::vec3 position = glm::vec3{ (i == 0) ? 525 : 20 , 10, 0 };
		glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
		glm::vec3 scale    = glm::vec3{ 1,  1, 1 };
		std::shared_ptr<dae::GameObject> pQbertUIGO = std::make_shared<dae::GameObject>(position, rotation, scale);
		std::shared_ptr<Helheim::TextComponent> pTextComponent0 = std::make_shared<Helheim::TextComponent>(pQbertUIGO.get(), "Lives left: 3", pHealthFont);
		pQbertUIGO->AddComponent(pTextComponent0);
		pQbertUIGO->SetName("Health UI - P" + std::to_string(i + 1));
		scene.Add(pQbertUIGO);

		// Score UI
		position = glm::vec3{ (i == 0) ? 525 : 20, 30, 0 };
		rotation = glm::vec3{ 0,  0, 0 };
		scale    = glm::vec3{ 1,  1, 1 };
		std::shared_ptr<dae::GameObject> pScoreUIGO = std::make_shared<dae::GameObject>(position, rotation, scale);
		std::shared_ptr<Helheim::TextComponent> pTextComponent1 = std::make_shared<Helheim::TextComponent>(pScoreUIGO.get(), "Score: 0", pHealthFont);
		pScoreUIGO->AddComponent(pTextComponent1);
		pScoreUIGO->SetName("Score UI - P" + std::to_string(i + 1));
		scene.Add(pScoreUIGO);

		// QBERT itself
		position = glm::vec3{ 200 + (i * 100),   424,    0 };
		rotation = glm::vec3{ 0,     0,    0 };
		scale    = glm::vec3{ 0.1f,  0.1f, 0.1f };
		std::shared_ptr<dae::GameObject> pQbertGO = std::make_shared<dae::GameObject>(position, rotation, scale);
		std::shared_ptr<Helheim::TextureComponent> pTextureComponent = std::make_shared<Helheim::TextureComponent>("Qbert.png", pQbertGO.get());
		std::shared_ptr<Helheim::HealthComponent> pHealthComponent = std::make_shared<Helheim::HealthComponent>(pQbertGO.get(), 10, 3);
		std::shared_ptr<Helheim::ScoreComponent> pScoreComponent = std::make_shared<Helheim::ScoreComponent>(pQbertGO.get());
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
void Helheim::Minigin::CreateLEVEL(dae::Scene& scene) const
{
	UNREFERENCED_PARAMETER(scene);

	std::shared_ptr<dae::GameObject> player1{ scene.GetObjectByName("Score UI - P1") };
	std::shared_ptr<dae::GameObject> player2{ scene.GetObjectByName("Score UI - P2") };

	// Level - Cube
	glm::vec3 position = glm::vec3{ 400, 200, 0 };
	glm::vec3 rotation = glm::vec3{ 0,   0, 0 };
	glm::vec3 scale    = glm::vec3{   1,   1, 1 };

	std::shared_ptr<dae::GameObject> pLevelGO = std::make_shared<dae::GameObject>(position, rotation, scale);
	std::shared_ptr<Helheim::Score> pScoreObserver = std::make_shared<Helheim::Score>(player1, player2);
	std::shared_ptr<Helheim::LevelComponent> pLevelComponent = std::make_shared<Helheim::LevelComponent>(pLevelGO.get(), glm::vec3(1, 0, 0));
	pLevelComponent->AddObserver(pScoreObserver);
	pLevelGO->AddComponent(pLevelComponent);
	pLevelGO->SetName("LevelCube");
	scene.Add(pLevelGO);
}