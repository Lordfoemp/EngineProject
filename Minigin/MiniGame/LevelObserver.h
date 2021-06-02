#pragma once
#include <Observer.h>

namespace Helheim
{
	class LevelObserver final : public Observer
	{
		public:
			LevelObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~LevelObserver() = default;

			LevelObserver(const LevelObserver&) = delete;
			LevelObserver(LevelObserver&&) noexcept = delete;
			LevelObserver& operator=(const LevelObserver&) = delete;
			LevelObserver& operator=(LevelObserver&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject * pObject, const OBSERVER_EVENTS & event) override;

		protected:

		private:
	};
}