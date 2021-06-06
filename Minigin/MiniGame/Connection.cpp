#include "MiniGamePCH.h"
#include "Connection.h"

Helheim::Connection::Connection(GameObject* pCube1, GameObject* pCube2, bool connectedToDisc)
	: m_pCube1(nullptr)
	, m_pCube2(nullptr)
	, m_pDisc(nullptr)
{
	if (!connectedToDisc)
	{
		m_pCube1 = pCube1;
		m_pCube2 = pCube2;
	}
	else
	{
		m_pCube1 = pCube1;
		m_pCube2 = nullptr;
		m_pDisc = pCube2;
	}
}
