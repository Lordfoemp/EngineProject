#pragma once
#include <Observer.h>

namespace Helheim
{
	class ColliderObserver : public Observer
	{
		public:
			ColliderObserver();
			virtual ~ColliderObserver() = default;

			ColliderObserver(const ColliderObserver&) = delete;
			ColliderObserver(ColliderObserver&&) noexcept = delete;
			ColliderObserver& operator=(const ColliderObserver&) = delete;
			ColliderObserver& operator=(ColliderObserver&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject * pObject, const OBSERVER_EVENTS & event) override;

		protected:

		private:
	};
}