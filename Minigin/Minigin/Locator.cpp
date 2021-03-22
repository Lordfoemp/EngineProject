#include "MiniginPCH.h"
#include "Locator.h"

#include "Audio.h"
#include "Timer.h"
#include "Renderer.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

Helheim::Locator::~Locator()
{
	m_pAudioService->~Audio();
	DELETE_POINTER(m_pAudioService);
	m_pRendererService->Destroy();
	DELETE_POINTER(m_pRendererService);
	DELETE_POINTER(m_pInputService);
	DELETE_POINTER(m_pResourceService);
	m_pSceneService->~SceneManager();
	DELETE_POINTER(m_pSceneService);
	m_pTimerService->~Timer();
	DELETE_POINTER(m_pTimerService);
}

// Renderer
void Helheim::Locator::ProvideRendererService(Renderer* pRendererService)
{ m_pRendererService = pRendererService; }



// Audio
void Helheim::Locator::ProvideAudioService(Audio* pAudioService)
{
	if (!pAudioService)
		m_pAudioService = new NullAudio();
	else
		m_pAudioService = pAudioService;
}

// Input
void Helheim::Locator::ProvideInputService(InputManager * pInputService)
{ m_pInputService = pInputService; }

// Resource
void Helheim::Locator::ProvideResourceService(ResourceManager * pResourceService)
{ m_pResourceService = pResourceService; }

// Scene
void Helheim::Locator::ProvideSceneService(SceneManager * pSceneService)
{ m_pSceneService = pSceneService; }

// Timer
void Helheim::Locator::ProvideTimerService(Timer* pTimerService)
{ m_pTimerService = pTimerService; }
