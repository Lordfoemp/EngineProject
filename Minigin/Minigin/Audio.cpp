#include "MiniginPCH.h"
#include "Audio.h"
#include "ResourceManager.h"

Helheim::Audio::~Audio()
{
	for (std::pair<int, Mix_Chunk*> pSound : m_Sounds)
	{
		Mix_FreeChunk(pSound.second);
		pSound.second = nullptr;
	}

	m_Sounds.clear();
}

void Helheim::Audio::Update()
{
	//m_Queue.Update();
}

void Helheim::Audio::AddSound(const std::string& filename, const AudioMessages& message)
{
	Mix_Chunk* audio{ Locator::GetResourceService()->LoadAudio(filename + ".wav") };
	m_Sounds.insert(std::pair<int, Mix_Chunk*>(int(message), audio));
}

// ------------------
// NULL audio
// ------------------
void Helheim::NullAudio::PlaySound(const AudioMessages&)
{}
void Helheim::NullAudio::StopSound(const int)
{}
void Helheim::NullAudio::StopAllSounds()
{}


// ------------------
// Console audio
// ------------------
Helheim::ConsoleAudio::ConsoleAudio()
{}
Helheim::ConsoleAudio::~ConsoleAudio()
{}

void Helheim::ConsoleAudio::PlaySound(const AudioMessages& message)
{
	Locator::GetEventQueue_AudioService()->PushToQueue(message);
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
void Helheim::LoggingAudio::PlaySound(const AudioMessages& message)
{
	std::cout << "Playing sound ID: " << int(message) << '\n';
}
void Helheim::LoggingAudio::StopSound(const int soundID)
{
	std::cout << "Stopping sound ID: " << soundID << '\n';
}
void Helheim::LoggingAudio::StopAllSounds()
{
	std::cout << "Stopping all sounds \n";
}