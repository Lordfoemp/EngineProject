#pragma once
#include "MiniginPCH.h"

#include <queue>
#include <deque>
#include <assert.h>

#include <SDL_mixer.h>

#include "Locator.h"
#include "Audio.h"

namespace Helheim
{
	template <typename T>
	class EventQueue
	{
		public:
			EventQueue() = default;
			~EventQueue() = default;

			EventQueue(const EventQueue& other) = delete;
			EventQueue(EventQueue&& other) noexcept = delete;
			EventQueue& operator=(const EventQueue& other) = delete;
			EventQueue& operator=(EventQueue&& other) noexcept = delete;

			virtual void ProcessQueue() = 0;

			T GetHead() const;
			void PushToQueue(const T& eventToPush);

			bool IsEmpty() const { return m_Queue.empty(); }

		protected:
			static const int MAX_PENDING = 16;
			T m_Queue[MAX_PENDING];
			int m_NumPending;

			int m_Head,
				m_Tail;
	};

	template <typename T>
	class EventQueue_Audio : public EventQueue<T>
	{
		public:
			EventQueue_Audio(Audio* pAudio);
			~EventQueue_Audio() = default;

			EventQueue_Audio(const EventQueue_Audio& other) = delete;
			EventQueue_Audio(EventQueue_Audio&& other) noexcept = delete;
			EventQueue_Audio& operator=(const EventQueue_Audio& other) = delete;
			EventQueue_Audio& operator=(EventQueue_Audio&& other) noexcept = delete;

			void ProcessQueue() override;

		private:
			Audio* m_pAudioService;
			void PlaySound(const int channel, Mix_Chunk* chunk, const int loops) const;
	};
}

// --------------
// Base class
// --------------
template<typename  T>
inline T Helheim::EventQueue<T>::GetHead() const
{
	/*if (!IsEmpty())
	{
		T event{ m_Queue.front() };
		m_Queue.pop();
		
		return event;
	}*/

	return T();
}

template<typename  T>
inline void Helheim::EventQueue<T>::PushToQueue(const T& eventToPush)
{
	assert((m_Tail + 1) % MAX_PENDING != m_Head);

	m_Queue[m_Tail] = eventToPush;
	m_Tail = (m_Tail + 1) % MAX_PENDING;
}

template<typename T>
inline Helheim::EventQueue_Audio<T>::EventQueue_Audio(Audio* pAudio)
								    : m_pAudioService(pAudio)
{}

// --------------
// Audio derived class
// --------------
template<typename T>
inline void Helheim::EventQueue_Audio<T>::ProcessQueue()
{
	// This(this->) is because the template parent of a template class is not instantiated 
	// during the compilation pass that first examines the template.
	if (this->m_Head == this->m_Tail)
		return;
	
	Mix_Chunk* toPlayAudio{ m_pAudioService->GetSoundFromSoundID(int(this->m_Queue[this->m_Head])) };
	while (!Mix_Playing(0))
	{
		PlaySound(0, toPlayAudio, 0);

		this->m_Head = (this->m_Head + 1) % this->MAX_PENDING;
	}		
}

template<typename T>
inline void Helheim::EventQueue_Audio<T>::PlaySound(const int channel, Mix_Chunk* chunk, const int loops) const
{
	Mix_PlayChannel(channel, chunk, loops);
}