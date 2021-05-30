#pragma once
#include "Game.h"

namespace Helheim
{
	class Scene_01;
	class QBertGame : public Game
	{
		public:
			QBertGame();
			virtual ~QBertGame();

			QBertGame(const QBertGame&) = delete;
			QBertGame(QBertGame&&) noexcept = delete;
			QBertGame& operator=(const QBertGame&) = delete;
			QBertGame& operator=(QBertGame&&) noexcept = delete;

			virtual void Initialize() override;
			virtual void GameLoop() override;

		protected:

		private:
			Scene_01* m_pScene_01;
			Scene_01* m_pScene_02;
			Scene_01* m_pScene_03;

			ConsoleAudio* m_pConsoleAudio;
			LoggingAudio* m_pLoggingAudio;
			SceneManager* m_pSceneManager;
			InputManager* m_pInputManager;
			ThreadManager* m_pThreadManager;
			ResourceManager* m_pResourceManager;

			void InitializeLocator();
			void InitializeSounds();

			void CleanUp();
	};
}