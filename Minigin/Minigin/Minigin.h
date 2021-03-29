#pragma once

struct SDL_Window;
namespace Helheim
{
	class Scene;
	class Minigin final
	{
		public:
			void Initialize();
			void LoadGame() const;
			void Cleanup();
			void Run();

		private:
			static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
			SDL_Window* m_pWindow{};

			Renderer* m_pRenderer;
			ConsoleAudio* m_pConsoleAudio;
			LoggingAudio* m_pLoggingAudio;
			SceneManager* m_pSceneManager;
			InputManager* m_pInputManager;
			ResourceManager* m_pResourceManager;

			void InitializeLocator();
			void InitializeSounds();

			void CreateBackground(Helheim::Scene& scene) const;
			void CreateLogo(Helheim::Scene& scene) const;
			void CreateFPSCounter(Helheim::Scene& scene) const;
			void CreateTitle(Helheim::Scene& scene) const;
			void CreateQBERTs(Helheim::Scene& scene) const;
			void CreateLEVEL(Helheim::Scene& scene) const;
	};
}