#pragma once
#include <Command.h>

namespace Helheim
{
	class QuitCommand final : public Command
	{
		public:
			QuitCommand() = default;;

			void Execute() override;

		private:
			void PressQuitButton();
	};
}