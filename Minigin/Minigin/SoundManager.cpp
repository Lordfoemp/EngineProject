#include "MiniginPCH.h"
#include "SoundManager.h"
#include <SDL_mixer.h>

dae::SoundManager::SoundManager()
{
	Initialize();
}
dae::SoundManager::~SoundManager()
{
	Mix_FreeChunk(m_pSFX);		m_pSFX   = nullptr;
	Mix_FreeMusic(m_pMusic);	m_pMusic = nullptr;
}

void dae::SoundManager::Initialize()
{
	m_pSFX = Mix_LoadWAV("./../Data/Sounds/drumloop.wav");
	m_pMusic = Mix_LoadMUS("./../Data/Sounds/wave.mp3");
}
void dae::SoundManager::Update()
{}

void dae::SoundManager::PlaySound(const int choice)
{
	switch (choice)
	{
		case 0:
			Mix_PlayChannel(0, m_pSFX, 0);
			break;
	}
	
}