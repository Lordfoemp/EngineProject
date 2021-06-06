#include "MiniGamePCH.h"
#include "EscapeCommand.h"

#include "JumpComponent.h"
#include "QBERTComponent.h"

Helheim::EscapeCommand::EscapeCommand(QBERT* pQBERT, GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp)
	: m_pQbert{ pQBERT }
	, m_pLevelGO{ pLevelGO }
	, m_JumpUp{ jumpUp }
	, m_JumpLeft{ jumpLeft }
{}
Helheim::EscapeCommand::EscapeCommand(GameObject* pQBERTGO, GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp)
	: m_pQbertGO{ pQBERTGO }
	, m_pLevelGO{ pLevelGO }
	, m_JumpUp{ jumpUp }
	, m_JumpLeft{ jumpLeft }
{}

void Helheim::EscapeCommand::Execute()
{
	Escape();
}

void Helheim::EscapeCommand::Escape()
{
	if (m_pQbert)
	{
		//// Disable all texture and enable the right one with the finding of a cube
		//m_pQbert->ResetAllSprites();
		//// Set the correct sprite when jumping
		//m_pQbert->SetJumpingSprite(m_JumpLeft, m_JumpUp);
		//m_pQbert->Escape(m_JumpLeft, m_JumpUp);
	}
	else
	{
		QBERTComponent* pQBERTComponent = m_pQbertGO->GetComponent<QBERTComponent>();
		pQBERTComponent->SetJumpingSprite(m_JumpLeft, m_JumpUp);

		JumpComponent* pJumpComponent = m_pQbertGO->GetComponent<JumpComponent>();
		pJumpComponent->Escape(m_JumpLeft, m_JumpUp);
	}
}
