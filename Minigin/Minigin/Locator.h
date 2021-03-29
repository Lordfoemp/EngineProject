#pragma once

namespace Helheim
{
	class Audio;
	class Renderer;
	class ConsoleAudio;
	class LoggingAudio;
	class SceneManager;
	class InputManager;
	class ResourceManager;
	class Locator final
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
			static void EnableAudioLogging();

			static void ProvideAudioService(Audio* pAudioService);
			static Audio* const GetAudioService() { return m_pAudioService; };

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
			static inline Audio* m_pAudioService = nullptr;

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