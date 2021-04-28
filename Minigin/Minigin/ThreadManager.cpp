#include "MiniginPCH.h"
#include "ThreadManager.h"

//#include <thread>

Helheim::ThreadManager::ThreadManager()
		: m_pThreads(std::vector<std::thread*>())
{}
Helheim::ThreadManager::~ThreadManager()
{
	for (size_t i{}; i < m_pThreads.size(); ++i)
	{
		if (m_pThreads[i]->joinable())
			m_pThreads[i]->join();

		DELETE_POINTER(m_pThreads[i]);
	}
}

void Helheim::ThreadManager::AddThread(std::thread* pThread)
{
	m_pThreads.push_back(pThread);
}