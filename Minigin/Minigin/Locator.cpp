#include "MiniginPCH.h"
#include "Locator.h"

#include "Audio.h"
#include "Timer.h"
#include "Renderer.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

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
void Helheim::Locator::ProvideEventQueue_Audio_Service(EventQueue_Audio<AudioMessages>* pEQ_Audio_Service)
{ m_pEventQueue_Audio = pEQ_Audio_Service; }

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