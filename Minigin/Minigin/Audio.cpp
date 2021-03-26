#include "MiniginPCH.h"
#include "Audio.h"
#include "ResourceManager.h"
#include "EventQueue.h"

Helheim::Audio::~Audio()
{
	for (std::pair<int, Mix_Chunk*> pSound : m_Sounds)
	{
		Mix_FreeChunk(pSound.second);
		pSound.second = nullptr;
	}

	m_Sounds.clear();
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
	Locator::GetEventQueue_AudioService()->Push(message);
}
void Helheim::ConsoleAudio::StopSound(const int soundID)
{
	Mix_HaltChannel(soundID);
}
void Helheim::ConsoleAudio::StopAllSounds()
{}

// ------------------
// Logging audio
// ------------------
void Helheim::LoggingAudio::PlaySound(const AudioMessages& message)
{
	std::cout << "Playing sound ID: " << int(message) << '\n';
}
void Helheim::LoggingAudio::StopSound(const int channelID)
{
	std::cout << "Stopping channel ID: " << channelID << '\n';
}
void Helheim::LoggingAudio::StopAllSounds()
{
	std::cout << "Stopping all sounds \n";
}