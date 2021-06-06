#pragma once
#include <Observer.h>

namespace Helheim
{
	class DiscObserver : public Observer
	{
		public:
			DiscObserver();
			virtual ~DiscObserver() = default;

			DiscObserver(const DiscObserver&) = delete;
			DiscObserver(DiscObserver&&) noexcept = delete;
			DiscObserver& operator=(const DiscObserver&) = delete;
			DiscObserver& operator=(DiscObserver&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject * pObject, const OBSERVER_EVENTS & event) override;

		protected:

		private:
	};
}
