#pragma once
#include "Game.h"
namespace Helheim
{
	class QBertGame : public Game
	{
		public:
			QBertGame();
			virtual ~QBertGame();

			QBertGame(const QBertGame&) = delete;
			QBertGame(QBertGame&&) noexcept = delete;
			QBertGame& operator=(const QBertGame&) = delete;
			QBertGame& operator=(QBertGame&&) noexcept = delete;

			void virtual Initialize() override;
			void virtual GameLoop() override;

		protected:

		private:
	};
}