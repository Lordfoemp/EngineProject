#pragma once
#include <Command.h>

namespace Helheim
{
	class PlayCommand final : public Command
	{
		public:
			PlayCommand() = default;;

			void Execute() override;

		private:
			void PressPlayButton();
	};
}