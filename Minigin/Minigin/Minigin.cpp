#include "MiniginPCH.h"
#include "Minigin.h"

// External Includes
#include <chrono>
#include <thread>
#include <SDL.h>

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
#include "TextComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"

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

/**
 * Code constructing the scene world starts here
 */
void Helheim::Minigin::LoadGame() const
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	
	std::shared_ptr<dae::Font> pFpsFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };
	std::shared_ptr<dae::Font> pTitleFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 40) };

	std::shared_ptr<dae::GameObject> pBackgroundGO = std::make_shared<dae::GameObject>(glm::vec3(0, 0, 0));
	std::shared_ptr<Helheim::TextureComponent> pTextureComp1 = std::make_shared<Helheim::TextureComponent>("background.jpg", pBackgroundGO);
	pBackgroundGO->AddComponent(pTextureComp1);
	scene.Add(pBackgroundGO);
	
	std::shared_ptr<dae::GameObject> pLogoGO = std::make_shared<dae::GameObject>(glm::vec3(216, 180, 0));
	std::shared_ptr<Helheim::TextureComponent> pTextureComp2 = std::make_shared<Helheim::TextureComponent>("logo.png", pLogoGO);
	pLogoGO->AddComponent(pTextureComp2);
	scene.Add(pLogoGO);

	std::shared_ptr<dae::GameObject> pFpsGO = std::make_shared<dae::GameObject>(glm::vec3(0, 0, 0));
	std::shared_ptr<Helheim::FPSComponent> pFPSComp = std::make_shared<Helheim::FPSComponent>(pFpsGO, pFpsFont);
	pFpsGO->AddComponent(pFPSComp);
	scene.Add(pFpsGO);

	std::shared_ptr<dae::GameObject> pTitleGO = std::make_shared<dae::GameObject>(glm::vec3(60, 50, 0));
	std::shared_ptr<Helheim::TextComponent> pTextComp = std::make_shared<Helheim::TextComponent>(pTitleGO, "Programming 4 Assignment", pTitleFont);
	pTitleGO->AddComponent(pTextComp);
	scene.Add(pTitleGO);
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
