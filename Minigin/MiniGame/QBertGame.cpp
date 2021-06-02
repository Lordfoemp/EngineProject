#include "MiniGamePCH.h"
#include "QBertGame.h"

#include "Locator.h"
#include "Audio.h"

#include "Audio.h"
#include "Timer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ThreadManager.h"
#include "ResourceManager.h"

#include "Scene_01.h"
#include "Scene_02.h"
#include "Scene_03.h"

#include "QBERT.h"

Helheim::QBertGame::QBertGame()
	: m_pScene_01(nullptr)
	, m_pScene_02(nullptr)
	, m_pScene_03(nullptr)
	, m_pConsoleAudio(nullptr)
	, m_pLoggingAudio(nullptr)
	, m_pSceneManager(nullptr)
	, m_pInputManager(nullptr)
	, m_pThreadManager(nullptr)
	, m_pResourceManager(nullptr)
{}
Helheim::QBertGame::~QBertGame()
{
	m_pEngine->Cleanup();
}

void Helheim::QBertGame::Initialize()
{
	m_pEngine->Initialize(640, 480);
	InitializeLocator();

	m_pQBERT = new QBERT("Player 1");
	m_pQBERT->Initialize({ 640 / 2 + 10, 80, 10 });

	// Create, Initialize and add the needed scenes
	m_pScene_01 = new Scene_01(640, 480, true);
	m_pScene_01->Initialize();
	Locator::GetSceneService()->AddScene(m_pScene_01);

	m_pScene_02 = new Scene_02(640, 480, false);
	m_pScene_02->Initialize();
	Locator::GetSceneService()->AddScene(m_pScene_02);

	m_pScene_03 = new Scene_03(640, 480, false);
	m_pScene_03->Initialize();
	Locator::GetSceneService()->AddScene(m_pScene_03);

	m_pQBERT->AddToScene(m_pScene_01, 1);
	m_pQBERT->AddToScene(m_pScene_02, 2);
	m_pQBERT->AddToScene(m_pScene_03, 3);
}
void Helheim::QBertGame::GameLoop()
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

void Helheim::QBertGame::InitializeSounds()
{
	// When adding sounds, dont forget to add the message with the needed value in the enum class in "Events.h"
	static_cast<ConsoleAudio*>(Locator::GetAudioService())->AddSound("drumloop", AudioMessages::PLAYER_DIED);
	static_cast<ConsoleAudio*>(Locator::GetAudioService())->AddSound("shouting_1_meghan", AudioMessages::SCORE_UP);
}
void Helheim::QBertGame::InitializeLocator()
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
void Helheim::QBertGame::CleanUp()
{
}