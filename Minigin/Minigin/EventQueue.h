#pragma once
#include "MiniginPCH.h"

#include <queue>
#include <deque>

//#include <SDL_mixer.h>

//#include <assert.h>

namespace Helheim
{
	template <typename T>
	class EventQueue
	{
		public:
			EventQueue();
			~EventQueue() = default;

			EventQueue(const EventQueue& other) = delete;
			EventQueue(EventQueue&& other) noexcept = delete;
			EventQueue& operator=(const EventQueue& other) = delete;
			EventQueue& operator=(EventQueue&& other) noexcept = delete;

			T GetHeadEvent() const { return m_Queue[m_Head]; }
			int GetHeadIndex() const { return m_Head; }
			int IncrementHead()
			{
				this->m_Head = (this->m_Head + 1) % this->MAX_PENDING;
				return this->m_Head;
			}
			T GetTailEvent() const { return m_Queue[m_Tail]; }
			int GetTailIndex() const { return m_Tail; }

			//T Pop() const;
			void Push(const T& eventToPush);

			bool IsEmpty() const { return m_Queue.empty(); }
			
		protected:
			static const int MAX_PENDING = 16;
			T m_Queue[MAX_PENDING];
			int m_NumPending;

			int m_Head,
				m_Tail;

			bool HasRequestedEvent(const T& playMessage) const;
	};
}

template<typename T>
inline Helheim::EventQueue<T>::EventQueue()
							  : m_Queue()
							  , m_NumPending()
							  , m_Head()
							  , m_Tail()
{}

template<typename  T>
inline void Helheim::EventQueue<T>::Push(const T& eventToPush)
{
	std::cout << "Thread locked\n";
		
	//assert((m_Tail + 1) % MAX_PENDING != m_Head);

	if (!HasRequestedEvent(eventToPush))
	{
		m_Queue[m_Tail] = eventToPush;
		m_Tail = (m_Tail + 1) % MAX_PENDING;
	}	
}

template<typename T>
inline bool Helheim::EventQueue<T>::HasRequestedEvent(const T& playMessage) const
{
	bool hasRequestAlready{ false };
	for (size_t i{}; i < MAX_PENDING; i++)
		if (m_Queue[i].request == playMessage.request)
			hasRequestAlready = true;

	return false;
}
