#pragma once
#include "EventQueue.h"
#include "Events.h"

#include <SDL_mixer.h>
#include <map>

namespace Helheim
{
	class Audio
	{
		public:
			Audio() = default;
			virtual ~Audio();

			Audio(const Audio&) = delete;
			Audio(Audio&&) noexcept = delete;
			Audio& operator=(const Audio&) = delete;
			Audio& operator=(Audio&&) noexcept = delete;

			virtual void Update();

			virtual void PlaySound(const AudioMessages& message) = 0;
			virtual void StopSound(const int soundID) = 0;
			virtual void StopAllSounds() = 0;

			void AddSound(const std::string& filename, const AudioMessages& message);
			Mix_Chunk* GetSoundFromSoundID(const int soundID)
			{
				return m_Sounds[soundID];
			}

		protected:
			std::map<int, Mix_Chunk*> m_Sounds;

		private:

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

			virtual void PlaySound(const AudioMessages& message) override;
			virtual void StopSound(const int soundID) override;
			virtual void StopAllSounds() override;

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

			virtual void PlaySound(const AudioMessages& message) override;
			virtual void StopSound(const int soundID) override;
			virtual void StopAllSounds() override;

		protected:

		private:
	};

	class LoggingAudio : public Audio
	{
		public:
			LoggingAudio() = default;
			virtual ~LoggingAudio() = default;

			LoggingAudio(const LoggingAudio&) = delete;
			LoggingAudio(LoggingAudio&&) noexcept = delete;
			LoggingAudio& operator=(const LoggingAudio&) = delete;
			LoggingAudio& operator=(LoggingAudio&&) noexcept = delete;

			virtual void PlaySound(const AudioMessages& message) override;
			virtual void StopSound(const int soundID) override;
			virtual void StopAllSounds() override;

		protected:
		private:
	};
}