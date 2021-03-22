#pragma once

#include <SDL_mixer.h>
namespace Helheim
{
	class Audio
	{
		public:
			Audio() = default;
			virtual ~Audio() = default;

			Audio(const Audio&) = delete;
			Audio(Audio&&) noexcept = delete;
			Audio& operator=(const Audio&) = delete;
			Audio& operator=(Audio&&) noexcept = delete;

			virtual void PlaySound(const int soundID) = 0;
			virtual void StopSound(const int soundID) = 0;
			virtual void StopAllSounds() = 0;

		protected:
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

			virtual void PlaySound(const int soundID) override;
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

			virtual void PlaySound(const int soundID) override;
			virtual void StopSound(const int soundID) override;
			virtual void StopAllSounds() override;

		protected:

		private:
			Mix_Music* m_pMusic;	// Play
			Mix_Chunk* m_pSFX;		// PlayChannel
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

			virtual void PlaySound(const int soundID) override;
			virtual void StopSound(const int soundID) override;
			virtual void StopAllSounds() override;

		protected:
		private:
	};
}