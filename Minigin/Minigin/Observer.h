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
			enum class OBSERVER_EVENTS
			{
				PLAYER_DIED,
				COLOR_CHANGE,
				COILY_DEAD_DISC,
				CATCH_SLICK,
				CATCH_SAM
			};

			Observer() = default;
			virtual ~Observer() = default;

			Observer(const Observer&) = delete;
			Observer(Observer&&) noexcept = delete;
			Observer& operator=(const Observer&) = delete;
			Observer& operator=(Observer&&) noexcept = delete;

			virtual void OnNotify(std::shared_ptr<dae::GameObject>& pObject, const OBSERVER_EVENTS& event) = 0;

		protected:


		private:
	
	};
}