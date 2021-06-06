#pragma once
#include <Command.h>

namespace Helheim
{
	class JumpCommand final : public Command
	{
		public:
			JumpCommand(QBERT* pQBERT, GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp);
			JumpCommand(GameObject* pQBERTGO, GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp);

			void Execute() override;

		private:
			bool m_JumpUp;
			bool m_JumpLeft;
			QBERT* m_pQbert;
			GameObject* m_pQbertGO;
			GameObject* m_pLevelGO;

			void Jump();
	};
}