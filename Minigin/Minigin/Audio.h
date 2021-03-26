#pragma once
#include "EventQueue.h"
#include "Events.h"

#include <SDL_mixer.h>
#include <unordered_map>

#include <thread>
#include <mutex>
#include <condition_variable>

namespace Helheim
{
	class Audio
	{
		public:
			

			Audio();
			virtual ~Audio();

			Audio(const Audio&) = delete;
			Audio(Audio&&) noexcept = delete;
			Audio& operator=(const Audio&) = delete;
			Audio& operator=(Audio&&) noexcept = delete;

			virtual void RequestPlaySound(const AudioMessages& message) = 0;
			virtual void StopSound(const int channelID) = 0;
			virtual void StopAllSounds() = 0;

			virtual void ProcessQueue() = 0;

		protected:
			
			//EventQueue<AudioMessages> m_Queue;
			EventQueue<PlayMessage> m_Queue;

			mutable std::mutex m_Mutex;
			std::condition_variable m_CV;

		private:
			std::thread m_Thread;			
	};

	class NullAudio : public Audio
	{
		public:
			NullAudio() = default;
			virtual ~NullAudio() = default;

			NullAudio(const NullAudio&) = delete;
			NullAudio(NullAudio&&) noexcept = delete;
			NullAudio& operator=(const NullAudio&) = delete;
			NullAudio& operator=(NullAudio&&) noexcept = delete;

			virtual void RequestPlaySound(const AudioMessages& message) override;
			virtual void StopSound(const int channelID) override;
			virtual void StopAllSounds() override;

			virtual void ProcessQueue() override;

		protected:

		private:
	};

	class ConsoleAudio : public Audio
	{
		public:
			ConsoleAudio();
			virtual ~ConsoleAudio();

			ConsoleAudio(const ConsoleAudio&) = delete;
			ConsoleAudio(ConsoleAudio&&) noexcept = delete;
			ConsoleAudio& operator=(const ConsoleAudio&) = delete;
			ConsoleAudio& operator=(ConsoleAudio&&) noexcept = delete;

			virtual void ProcessQueue() override;

			virtual void RequestPlaySound(const AudioMessages& message) override;
			virtual void StopSound(const int channelID) override;
			virtual void StopAllSounds() override;

			void AddSound(const std::string& filename, const AudioMessages& message);

		protected:

		private:
			Mix_Chunk* GetSoundFromSoundID(const int soundID) { return m_Sounds[soundID]; }
			std::unordered_map<int, Mix_Chunk*> m_Sounds;
			std::unordered_map<int, AudioMessages> m_Channels;

			void PlaySound(const int channel, Mix_Chunk* chunk, const int loops, const int volume) const;
	};

	class LoggingAudio : public Audio
	{
		public:
			LoggingAudio(Audio* pConsoleAudio);
			virtual ~LoggingAudio() = default;

			LoggingAudio(const LoggingAudio&) = delete;
			LoggingAudio(LoggingAudio&&) noexcept = delete;
			LoggingAudio& operator=(const LoggingAudio&) = delete;
			LoggingAudio& operator=(LoggingAudio&&) noexcept = delete;

			virtual void ProcessQueue() override;

			virtual void RequestPlaySound(const AudioMessages& message) override;
			virtual void StopSound(const int channelID) override;
			virtual void StopAllSounds() override;

			void AddSound(const std::string& filename, const AudioMessages& message);
		protected:
		private:
			ConsoleAudio* m_pConsoleAudio;
	};
}