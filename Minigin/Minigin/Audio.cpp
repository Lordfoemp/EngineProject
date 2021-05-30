#include "MiniginPCH.h"
#include "Audio.h"
#include "ResourceManager.h"
#include "EventQueue.h"

//#include <SDL.h>
#include "Locator.h"
#include "ThreadManager.h"

Helheim::Audio::Audio()
	    : m_IsProcessingQueue(true)
{
	Locator::GetThreadService()->AddThread(new std::thread(&Audio::ProcessQueue, std::ref(*this)));
}
Helheim::Audio::~Audio()
{
	DisableIsProccesingQueue();
}

// ------------------
// NULL audio
// ------------------
void Helheim::NullAudio::RequestPlaySound(const AudioMessages&)
{}
void Helheim::NullAudio::StopSound(const int)
{}
void Helheim::NullAudio::StopAllSounds()
{}

void Helheim::NullAudio::ProcessQueue()
{}

// ------------------
// Console audio
// ------------------
Helheim::ConsoleAudio::ConsoleAudio()
{}
Helheim::ConsoleAudio::~ConsoleAudio()
{
	for (std::pair<int, Mix_Chunk*> pSound : m_Sounds)
	{
		Mix_FreeChunk(pSound.second);
		pSound.second = nullptr;
	}

	m_Sounds.clear();
	m_CV.notify_all();
}

void Helheim::ConsoleAudio::ProcessQueue()
{
	while (m_IsProcessingQueue)
	{
		// lock the mutex
		std::unique_lock<std::mutex> lock(m_Mutex);
	
		int headID{ m_Queue.GetHeadIndex() };
		int tailID{ m_Queue.GetTailIndex() };
	
		while (headID != tailID)
		{
			PlayMessage playMessage{ m_Queue.GetHeadEvent() };
	
			Mix_Chunk* toPlayAudio{ GetSoundFromSoundID(int(playMessage.request)) };
			PlaySound(-1, toPlayAudio, 0, playMessage.volume);
			headID = m_Queue.IncrementHead();
		} 		
		
		headID = m_Queue.GetHeadIndex();
		tailID = m_Queue.GetTailIndex();
		
		//if (headID == tailID)
		//	m_CV.wait(lock);
		//else
		//	lock.unlock();
	}
}

void Helheim::ConsoleAudio::RequestPlaySound(const AudioMessages& message)
{
	// lock the mutex
	std::lock_guard<std::mutex> lock(m_Mutex);

	PlayMessage playMessage{};
	playMessage.request = message;
	playMessage.volume = 64;
	playMessage.isPlaying = false;

	m_Queue.Push(playMessage);

	// unlock the thread
	m_CV.notify_one();
}
void Helheim::ConsoleAudio::StopSound(const int soundID)
{
	Mix_HaltChannel(soundID);
}
void Helheim::ConsoleAudio::StopAllSounds()
{}

void Helheim::ConsoleAudio::AddSound(const std::string& filename, const AudioMessages& message)
{
	Mix_Chunk* audio{ Locator::GetResourceService()->LoadAudio((filename + ".wav"), "QBERT/Sounds/") };
	m_Sounds.insert(std::pair<int, Mix_Chunk*>(int(message), audio));
}
void Helheim::ConsoleAudio::PlaySound(const int channel, Mix_Chunk* chunk, const int loops, const int volume) const
{
	Mix_VolumeChunk(chunk, volume);

	int channelCheck{ Mix_PlayChannel(channel, chunk, loops) };
	if (channelCheck < 0)
		return;

	SDL_Delay(100);
}

// ------------------
// Logging audio
// ------------------
Helheim::LoggingAudio::LoggingAudio(Audio* pConsoleAudio)
					  : m_pConsoleAudio(dynamic_cast<ConsoleAudio*>(pConsoleAudio))
{}
Helheim::LoggingAudio::~LoggingAudio()
{
	//DELETE_POINTER(m_pConsoleAudio);
	m_pConsoleAudio = nullptr;
}

void Helheim::LoggingAudio::ProcessQueue()
{
	//m_pConsoleAudio->ProcessQueue();
}

void Helheim::LoggingAudio::RequestPlaySound(const AudioMessages& message)
{
	std::cout << "Playing sound ID: " << int(message) << '\n';
	m_pConsoleAudio->RequestPlaySound(message);
}
void Helheim::LoggingAudio::StopSound(const int channelID)
{
	std::cout << "Stopping channel ID: " << channelID << '\n';
	m_pConsoleAudio->StopSound(channelID);
}
void Helheim::LoggingAudio::StopAllSounds()
{
	std::cout << "Stopping all sounds \n";
	m_pConsoleAudio->StopAllSounds();
}

void Helheim::LoggingAudio::AddSound(const std::string& filename, const AudioMessages& message)
{
	std::cout << "Adding sound \n";
	m_pConsoleAudio->AddSound(filename, message);
}