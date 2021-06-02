#pragma once
#include <Observer.h>

namespace Helheim
{
	class HealthObserver final : public Observer
	{
		public:
			HealthObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~HealthObserver() = default;

			HealthObserver(const HealthObserver&) = delete;
			HealthObserver(HealthObserver&&) noexcept = delete;
			HealthObserver& operator=(const HealthObserver&) = delete;
			HealthObserver& operator=(HealthObserver&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event) override;

		protected:

		private:
	};
}