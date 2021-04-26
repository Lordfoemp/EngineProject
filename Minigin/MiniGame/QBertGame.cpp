#include "QBertGame.h"

Helheim::QBertGame::QBertGame()
{}
Helheim::QBertGame::~QBertGame()
{
	m_pEngine->Cleanup();
}

void Helheim::QBertGame::Initialize()
{
	m_pEngine->Initialize();
	m_pEngine->LoadGame();
}
void Helheim::QBertGame::GameLoop()
{
	m_pEngine->Run();
}