#pragma once
#include "Singleton.h"

#include <chrono>

namespace Helheim
{
	class Timer final : public dae::Singleton<Timer>
	{
		public:
			Timer();
			~Timer() = default;

			Timer(const Timer&) = delete;
			Timer(Timer&&) noexcept = delete;
			Timer& operator=(const Timer&) = delete;
			Timer& operator=(Timer&&) noexcept = delete;

			void Update();

			const float GetElapsedTime() const { return m_ElapsedTime; }
			const float GetMsEachUpdate() const { return m_MsEachUpdate; }
			const float GetLag() const { return m_Lag; }
			void SubtractFixedUpdateFromLag() { m_Lag -= m_MsEachUpdate; }

			void ResetElapsedTime() { m_ElapsedTime = 0; }
		protected:

		private:
			std::chrono::steady_clock::time_point m_CurrentTime;
			std::chrono::steady_clock::time_point m_PreviousTime;
			float m_Lag;
			float m_ElapsedTime;
			float m_MsEachUpdate;
			static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	};
}