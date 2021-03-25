//#pragma once
//#include "EventQueue.h"
//#include "Events.h"
//
////#include <SDL_mixer.h>
//
//namespace Helheim
//{
//	class AudioOLD
//	{
//		public:
//			AudioOLD() = default;
//			virtual ~AudioOLD() = default;
//
//			AudioOLD(const AudioOLD&) = delete;
//			AudioOLD(AudioOLD&&) noexcept = delete;
//			AudioOLD& operator=(const AudioOLD&) = delete;
//			AudioOLD& operator=(AudioOLD&&) noexcept = delete;
//
//			virtual void Update();
//
//			virtual void PlaySound(const int soundID) = 0;
//			virtual void StopSound(const int soundID) = 0;
//			virtual void StopAllSounds() = 0;
//
//		protected:
//			//Node<int> m_Node;
//			//EventQueue<AudioMessages> m_Queue;
//
//		private:
//
//	};
//	
//	class NullAudioOLD : public AudioOLD
//	{
//		public:
//			NullAudioOLD() = default;
//			virtual ~NullAudioOLD() = default;
//
//			NullAudioOLD(const NullAudioOLD&) = delete;
//			NullAudioOLD(NullAudioOLD&&) noexcept = delete;
//			NullAudioOLD& operator=(const NullAudioOLD&) = delete;
//			NullAudioOLD& operator=(NullAudioOLD&&) noexcept = delete;
//
//			virtual void PlaySound(const int soundID) override;
//			virtual void StopSound(const int soundID) override;
//			virtual void StopAllSounds() override;
//
//		protected:
//
//		private:
//	};
//
//	class ConsoleAudioOLD : public AudioOLD
//	{
//		public:
//			ConsoleAudioOLD();
//			virtual ~ConsoleAudioOLD();
//
//			ConsoleAudioOLD(const ConsoleAudioOLD&) = delete;
//			ConsoleAudioOLD(ConsoleAudioOLD&&) noexcept = delete;
//			ConsoleAudioOLD& operator=(const ConsoleAudioOLD&) = delete;
//			ConsoleAudioOLD& operator=(ConsoleAudioOLD&&) noexcept = delete;
//
//			virtual void PlaySound(const int soundID) override;
//			virtual void StopSound(const int soundID) override;
//			virtual void StopAllSounds() override;
//
//		protected:
//
//		private:
//			//Mix_Music* m_pMusic;	// Play
//			//Mix_Chunk* m_pSFX;		// PlayChannel
//	};
//
//	class LoggingAudioOLD : public AudioOLD
//	{
//		public:
//			LoggingAudioOLD() = default;
//			virtual ~LoggingAudioOLD() = default;
//
//			LoggingAudioOLD(const LoggingAudioOLD&) = delete;
//			LoggingAudioOLD(LoggingAudioOLD&&) noexcept = delete;
//			LoggingAudioOLD& operator=(const LoggingAudioOLD&) = delete;
//			LoggingAudioOLD& operator=(LoggingAudioOLD&&) noexcept = delete;
//
//			virtual void PlaySound(const int soundID) override;
//			virtual void StopSound(const int soundID) override;
//			virtual void StopAllSounds() override;
//
//		protected:
//		private:
//	};
//}