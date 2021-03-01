#pragma once
#include <vector>

namespace dae
{
	class GameObject;
}
namespace Helheim
{
	class Observer
	{
		public:
			enum class OBSERVER_EVENTS : int
			{
				NO_EVENT = 0,
				PLAYER_DIED_P1,
				PLAYER_DIED_P2,
				COLOR_CHANGE_P1,
				COLOR_CHANGE_P2,
				COILY_DEAD_DISC_P1,
				COILY_DEAD_DISC_P2,
				CATCH_SLICK_P1,
				CATCH_SLICK_P2,
				CATCH_SAM_P1,
				CATCH_SAM_P2
			};

			Observer(const std::shared_ptr<dae::GameObject>& pMessageRecieverP1, const std::shared_ptr<dae::GameObject>& pMessageRecieverP2);
			virtual ~Observer() = default;

			Observer(const Observer&) = delete;
			Observer(Observer&&) noexcept = delete;
			Observer& operator=(const Observer&) = delete;
			Observer& operator=(Observer&&) noexcept = delete;

			virtual void OnNotify(dae::GameObject* pObject, const OBSERVER_EVENTS& event) = 0;

		protected:
			std::shared_ptr<dae::GameObject> m_pMessageReceiverP1;
			std::shared_ptr<dae::GameObject> m_pMessageReceiverP2;

		private:
	};
}