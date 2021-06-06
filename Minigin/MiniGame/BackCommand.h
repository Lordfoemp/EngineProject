#pragma once
#include <Command.h>

namespace Helheim
{
	class BackCommand final : public Command
	{
		public:
			BackCommand() = default;

			void Execute() override;

		private:
			void PressBackButton();
	};
}