#include "MiniGamePCH.h"
#include "DemoGame.h"

#include "Audio.h"
#include "Timer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ThreadManager.h"
#include "ResourceManager.h"

#include "Scene_Demo.h"

Helheim::DemoGame::DemoGame()
	: m_pSceneDemo(nullptr)
	, m_pConsoleAudio(nullptr)
	, m_pLoggingAudio(nullptr)
	, m_pSceneManager(nullptr)
	, m_pInputManager(nullptr)
	, m_pThreadManager(nullptr)
	, m_pResourceManager(nullptr)
{}
Helheim::DemoGame::~DemoGame()
{
	m_pEngine->Cleanup();
}

void Helheim::DemoGame::Initialize()
{
	m_pEngine->Initialize(640, 480);
	InitializeLocator();

	// Create, Initialize and add the needed scenes
	m_pSceneDemo = new Scene_Demo(640, 480);
	m_pSceneDemo->Initialize();
	Locator::GetSceneService()->AddGameScene(m_pSceneDemo);
}
void Helheim::DemoGame::GameLoop()
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

	CleanUp();
}

void Helheim::DemoGame::InitializeLocator()
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

}
void Helheim::DemoGame::CleanUp()
{
}