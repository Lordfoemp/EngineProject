#pragma once
#include "Observer.h"

namespace Helheim
{
	class GameObject;
}
namespace Helheim
{
	class TextComponent;
	class HealthComponent;
	class Health final : public Observer
	{
		public: 
			Health(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~Health() = default;

			Health(const Health&) = delete;
			Health(Health&&) noexcept = delete;
			Health& operator=(const Health&) = delete;
			Health& operator=(Health&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS & event) override;

		protected:

		private:
			Helheim::GameObject* m_pMessageReceiver;
	};

	class Score final : public Observer
	{
		public:
			Score(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~Score() = default;

			Score(const Score&) = delete;
			Score(Score&&) noexcept = delete;
			Score& operator=(const Score&) = delete;
			Score& operator=(Score&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event) override;

		protected:

		private:
			int m_Score;
	};
}