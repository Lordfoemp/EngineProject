#include "MiniGamePCH.h"
#include "Game.h"

Helheim::Game::Game()
		: m_pEngine(new Minigin())
{}

Helheim::Game::~Game()
{
	if (m_pEngine != nullptr)
	{
		delete m_pEngine;
		m_pEngine = nullptr;
	}
}