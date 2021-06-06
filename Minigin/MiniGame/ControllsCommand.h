#pragma once
#include <Command.h>

namespace Helheim
{
	class ControllsCommand final : public Command
	{
		public:
			ControllsCommand() = default;

			void Execute() override;

		private:
			void PressControllsButton();
	};
}