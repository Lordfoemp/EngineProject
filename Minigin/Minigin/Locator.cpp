#include "MiniginPCH.h"
#include "Locator.h"

// Renderer
void Helheim::Locator::ProvideRendererService(Renderer* pRendererService)
{ m_pRendererService = pRendererService; }

// Audio
void Helheim::Locator::ProvideConsoleAudioService(ConsoleAudio* pAudioService)
{ m_pAudioConsoleService = pAudioService; }
void Helheim::Locator::ProvideAudioLoggingService(LoggingAudio* pAudioService)
{ m_pAudioLoggingService = pAudioService; }

// Input
void Helheim::Locator::ProvideInputService(InputManager * pInputService)
{ m_pInputService = pInputService; }

// Resource
void Helheim::Locator::ProvideResourceService(ResourceManager * pResourceService)
{ m_pResourceService = pResourceService; }

// Scene
void Helheim::Locator::ProvideSceneService(SceneManager * pSceneService)
{ m_pSceneService = pSceneService; }