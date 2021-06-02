#pragma once
#include <Observer.h>

namespace Helheim
{
	class ScoreObserver final : public Observer
	{
		public:
			ScoreObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~ScoreObserver() = default;

			ScoreObserver(const ScoreObserver&) = delete;
			ScoreObserver(ScoreObserver&&) noexcept = delete;
			ScoreObserver& operator=(const ScoreObserver&) = delete;
			ScoreObserver& operator=(ScoreObserver&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event) override;

		protected:

		private:
	};
}