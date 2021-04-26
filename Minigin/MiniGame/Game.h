#pragma once
#include <Minigin.h>

namespace Helheim
{	
	class Game
	{
		public:
			Game();
			virtual ~Game();

			Game(const Game&) = delete;
			Game(Game&&) noexcept = delete;
			Game& operator=(const Game&) = delete;
			Game& operator=(Game&&) noexcept = delete;

			virtual void Initialize() = 0;
			virtual void GameLoop() = 0;

		protected:
			Minigin* m_pEngine;

		private:
	};
}