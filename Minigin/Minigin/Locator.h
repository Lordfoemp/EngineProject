#pragma once

namespace Helheim
{
	class ConsoleAudio;
	class LoggingAudio;
	class Renderer;
	class InputManager;
	class ResourceManager;
	class SceneManager;
	class Locator
	{
		public:
			Locator() = default;
			~Locator() = default;

			Locator(const Locator&) = delete;
			Locator(Locator&&) noexcept = delete;
			Locator& operator=(const Locator&) = delete;
			Locator& operator=(Locator&&) noexcept = delete;

			// Renderer
			static void ProvideRendererService(Renderer* pAudioService);
			static Renderer* const GetRendererService() { return m_pRendererService; }

			// Audio
			static void ProvideConsoleAudioService(ConsoleAudio* pAudioService);
			static void ProvideAudioLoggingService(LoggingAudio* pAudioService);
			static ConsoleAudio* const GetConsoleAudioService() { return m_pAudioConsoleService; }
			static LoggingAudio* const GetLoggingAudioService() { return m_pAudioLoggingService; }

			// Input
			static void ProvideInputService(InputManager* pInputService);
			static InputManager* const GetInputService() { return m_pInputService; }

			// Resource
			static void ProvideResourceService(ResourceManager* pResourceService);
			static ResourceManager* const GetResourceService() { return m_pResourceService; }

			// Scene
			static void ProvideSceneService(SceneManager* pSceneService);
			static SceneManager* const GetSceneService() { return m_pSceneService; }

		private:
			// Audio
			static inline ConsoleAudio* m_pAudioConsoleService = nullptr;
			static inline LoggingAudio* m_pAudioLoggingService = nullptr;

			// Rendering
			static inline Renderer* m_pRendererService = nullptr;
			
			// InputManager	
			static inline InputManager* m_pInputService = nullptr;

			// ResourceManager	
			static inline ResourceManager* m_pResourceService = nullptr;
			
			// SceneManager	
			static inline SceneManager* m_pSceneService = nullptr;
	};
}