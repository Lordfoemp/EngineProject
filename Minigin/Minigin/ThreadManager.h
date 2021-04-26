#pragma once
#include <vector>

namespace Helheim
{
	class ThreadManager
	{
		public:
			ThreadManager();
			~ThreadManager();

			ThreadManager(const ThreadManager&) = delete;
			ThreadManager(ThreadManager&&) noexcept = delete;
			ThreadManager& operator=(const ThreadManager&) = delete;
			ThreadManager& operator=(ThreadManager&&) noexcept = delete;

			void AddThread(std::thread* pThread);

		protected:
			
		private:
			std::vector<std::thread*> m_pThreads;
	};
}
