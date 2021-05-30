#include "MiniginPCH.h"
#include "Minigin.h"

#include "Scene.h"

#include "Audio.h"
#include "Timer.h"
#include "Renderer.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "ThreadManager.h"
#include "ResourceManager.h"


//#include <SDL.h>

void Helheim::Minigin::Initialize(const int windowWidth, const int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	m_pWindow = SDL_CreateWindow( "Programming 4 assignment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL );
	if (!m_pWindow)
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		throw std::runtime_error(std::string("Mix_OpenAudio Error: ") + Mix_GetError());

	InitializeLocator();
	//InitializeSounds();
}

/**
 * Code constructing the scene world starts here
 */
void Helheim::Minigin::LoadGame() const
{
	//Helheim::Scene& scene = Locator::GetSceneService()->CreateScene("Demo");
	//
	//CreateBackground(scene);
	//CreateLogo(scene);
	//CreateFPSCounter(scene);
	//CreateTitle(scene);
	//CreateQBERTs(scene);
	//CreateLEVEL(scene);
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
//void Helheim::Minigin::InitializeSounds()
//{
//	// When adding sounds, dont forget to add the message with the needed value in the enum class in "Events.h"
//	m_pConsoleAudio->AddSound("drumloop", AudioMessages::PLAYER_DIED);
//	m_pConsoleAudio->AddSound("shouting_1_meghan", AudioMessages::SCORE_UP);
//}

