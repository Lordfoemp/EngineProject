#pragma once

namespace Helheim
{
	class Audio;
	class ConsoleAudio;
	class LoggingAudio;
	class Renderer;
	class InputManager;
	class ResourceManager;
	class SceneManager;
	class Timer;
	class Locator
	{
		public:
			Locator() = default;
			~Locator();

			Locator(const Locator&) = delete;
			Locator(Locator&&) noexcept = delete;
			Locator& operator=(const Locator&) = delete;
			Locator& operator=(Locator&&) noexcept = delete;

			// Renderer
			static void ProvideRendererService(Renderer* pAudioService);
			static Renderer* const GetRendererService() { return m_pRendererService; }

			// Audio
			static void ProvideAudioService(Audio* pAudioService);
			
			template <class T>
			static T* const GetAudioService();

			// Input
			static void ProvideInputService(InputManager* pInputService);
			static InputManager* const GetInputService() { return m_pInputService; }

			// Resource
			static void ProvideResourceService(ResourceManager* pResourceService);
			static ResourceManager* const GetResourceService() { return m_pResourceService; }

			// Scene
			static void ProvideSceneService(SceneManager* pSceneService);
			static SceneManager* const GetSceneService() { return m_pSceneService; }

			// Timer
			static void ProvideTimerService(Timer* pTimerService);
			static Timer* const GetTimerService() { return m_pTimerService; }

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

			// Timer	
			static inline Timer* m_pTimerService = nullptr;
	};

	template<class T>
	inline T* const Locator::GetAudioService()
	{
		T* pTAudioService = dynamic_cast<T*>(m_pAudioService);
		if (pTAudioService)
			return pTAudioService;

		return nullptr;
	}
}