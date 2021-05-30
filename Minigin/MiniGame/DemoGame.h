#pragma once
#include "Game.h"

namespace Helheim
{
	class Scene_Demo;
	class DemoGame : public Game
	{
		public:
			DemoGame();
			virtual ~DemoGame();

			DemoGame(const DemoGame&) = delete;
			DemoGame(DemoGame&&) noexcept = delete;
			DemoGame& operator=(const DemoGame&) = delete;
			DemoGame& operator=(DemoGame&&) noexcept = delete;

			void virtual Initialize() override;
			void virtual GameLoop() override;

		protected:

		private:
			Scene_Demo* m_pSceneDemo;

			ConsoleAudio* m_pConsoleAudio;
			LoggingAudio* m_pLoggingAudio;
			SceneManager* m_pSceneManager;
			InputManager* m_pInputManager;
			ThreadManager* m_pThreadManager;
			ResourceManager* m_pResourceManager;

			void InitializeLocator();

			void CleanUp();
	};
}