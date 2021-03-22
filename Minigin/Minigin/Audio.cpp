#include "MiniginPCH.h"
#include "Audio.h"
#include <SDL_mixer.h>

#include "ResourceManager.h"

// ------------------
// NULL audio
// ------------------
void Helheim::NullAudio::PlaySound(const int)
{}
void Helheim::NullAudio::StopSound(const int)
{}
void Helheim::NullAudio::StopAllSounds()
{}


// ------------------
// Console audio
// ------------------
Helheim::ConsoleAudio::ConsoleAudio()
	    : m_pMusic(nullptr)
	    , m_pSFX(nullptr)
{
	m_pSFX = Locator::GetResourceService()->LoadAudio("drumloop.wav");
	//m_pSFX = Helheim::ResourceManager::GetInstance().LoadAudio("drumloop.wav");
	m_pMusic = Locator::GetResourceService()->LoadMusic("drumloop.wav");
	//m_pMusic = Helheim::ResourceManager::GetInstance().LoadMusic("drumloop.wav");
}
Helheim::ConsoleAudio::~ConsoleAudio()
{
	Mix_FreeChunk(m_pSFX);		m_pSFX = nullptr;
	Mix_FreeMusic(m_pMusic);	m_pMusic = nullptr;
}

void Helheim::ConsoleAudio::PlaySound(const int soundID)
{
	switch (soundID)
	{
		case 0:
			Mix_PlayChannel(0, m_pSFX, 0);
			break;
		case 1:
			Mix_PlayMusic(m_pMusic, 0);
			break;
	}
}
void Helheim::ConsoleAudio::StopSound(const int soundID)
{
	switch (soundID)
	{
		case 0:
			Mix_HaltChannel(0);
			break;
		case 1:
			Mix_HaltMusic();
			break;
	}
}
void Helheim::ConsoleAudio::StopAllSounds()
{
	if (Mix_PlayingMusic())
	{
		auto x = Mix_GetMusicType;
		UNREFERENCED_PARAMETER(x);
	}
}

// ------------------
// Logging audio
// ------------------
void Helheim::LoggingAudio::PlaySound(const int soundID)
{
	std::cout << "Playing sound ID: " << soundID << '\n';
}
void Helheim::LoggingAudio::StopSound(const int soundID)
{
	std::cout << "Stopping sound ID: " << soundID << '\n';
}
void Helheim::LoggingAudio::StopAllSounds()
{
	std::cout << "Stopping all sounds \n";
}