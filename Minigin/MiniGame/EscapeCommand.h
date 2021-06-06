#pragma once
#include <Command.h>

namespace Helheim
{
	class EscapeCommand final : public Command
	{
		public:
			EscapeCommand(QBERT* pQBERT, GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp);
			EscapeCommand(GameObject* pQBERTGO, GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp);

			void Execute() override;

		private:
			bool m_JumpUp;
			bool m_JumpLeft;
			QBERT* m_pQbert;
			GameObject* m_pQbertGO;
			GameObject* m_pLevelGO;

			void Escape();
	};
}