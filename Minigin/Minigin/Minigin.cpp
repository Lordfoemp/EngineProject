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

using namespace std;
using namespace std::chrono;

void Helheim::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	m_Window = SDL_CreateWindow("Programming 4 assignment", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	if (!m_Window) 
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	dae::Renderer::GetInstance().Init(m_Window);

	InitializeConsole();
}

/**
 * Code constructing the scene world starts here
 */
void Helheim::Minigin::LoadGame() const
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	
	std::shared_ptr<dae::Font> pFpsFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };
	std::shared_ptr<dae::Font> pTitleFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 40) };
	std::shared_ptr<dae::Font> pHealthFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };

	std::shared_ptr<dae::GameObject> pBackgroundGO = std::make_shared<dae::GameObject>(glm::vec3(0, 0, 0));
	std::shared_ptr<Helheim::TextureComponent> pTextureComp1 = std::make_shared<Helheim::TextureComponent>("background.jpg", pBackgroundGO);
	pBackgroundGO->AddComponent(pTextureComp1);
	scene.Add(pBackgroundGO);
	
	std::shared_ptr<dae::GameObject> pLogoGO = std::make_shared<dae::GameObject>(glm::vec3(216, 180, 0));
	std::shared_ptr<Helheim::TextureComponent> pTextureComp2 = std::make_shared<Helheim::TextureComponent>("logo.png", pLogoGO);
	pLogoGO->AddComponent(pTextureComp2);
	scene.Add(pLogoGO);
	
	std::shared_ptr<dae::GameObject> pFpsGO = std::make_shared<dae::GameObject>(glm::vec3(20, 20, 0));
	std::shared_ptr<Helheim::FPSComponent> pFPSComp = std::make_shared<Helheim::FPSComponent>(pFpsGO, pFpsFont);
	pFpsGO->AddComponent(pFPSComp);
	scene.Add(pFpsGO);
	
	std::shared_ptr<dae::GameObject> pTitleGO = std::make_shared<dae::GameObject>(glm::vec3(60, 50, 0));
	std::shared_ptr<Helheim::TextComponent> pTextComp0 = std::make_shared<Helheim::TextComponent>(pTitleGO, "Programming 4 Assignment", pTitleFont);
	pTitleGO->AddComponent(pTextComp0);
	scene.Add(pTitleGO);

	glm::vec3 position = glm::vec3{ 525, 10, 0 };
	std::shared_ptr<dae::GameObject> pQbertUIGO = std::make_shared<dae::GameObject>(position);
	std::shared_ptr<Helheim::TextComponent> pTextComp1 = std::make_shared<Helheim::TextComponent>(pQbertUIGO, "Lives left: 3", pHealthFont);
	pQbertUIGO->AddComponent(pTextComp1);
	scene.Add(pQbertUIGO);

	position = glm::vec3{  200, 200, 0 }; 
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale = glm::vec3{ 0.1f,  0.1f, 0.1f };
	std::shared_ptr<dae::GameObject> pQbertGO = std::make_shared<dae::GameObject>(position, rotation, scale);
	std::shared_ptr<Helheim::TextureComponent> pTextureComp3 = std::make_shared<Helheim::TextureComponent>("Qbert.png", pQbertGO);
	std::shared_ptr<Helheim::Health> pHealthObserver = std::make_shared<Helheim::Health>(pQbertUIGO);	
	std::shared_ptr<Helheim::HealthComponent> pHealthComp = std::make_shared<Helheim::HealthComponent>(pQbertGO, 10, 3);
	pHealthComp->AddObserver(pHealthObserver);
	pQbertGO->AddComponent(pTextureComp3);
	pQbertGO->AddComponent(pHealthComp);
	scene.Add(pQbertGO);

	
}

void Helheim::Minigin::Cleanup()
{
	dae::Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
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
