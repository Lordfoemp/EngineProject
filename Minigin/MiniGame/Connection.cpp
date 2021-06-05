#include "MiniGamePCH.h"
#include "Connection.h"

Helheim::Connection::Connection(Cube* pCube1, Cube* pCube2)
	: m_pCube1(pCube1)
	, m_pCube2(pCube2)
	, m_pDisc(nullptr)
{}
Helheim::Connection::Connection(Cube* pCube1, Disc* pDisc)
	: m_pCube1(pCube1)
	, m_pCube2(nullptr)
	, m_pDisc(pDisc)
{}