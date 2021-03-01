#pragma once
#include "Observer.h"

namespace dae
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
			Health(const std::shared_ptr<dae::GameObject>& pMessageRecieverP1, const std::shared_ptr<dae::GameObject>& pMessageRecieverP2);
			virtual ~Health() = default;

			Health(const Health&) = delete;
			Health(Health&&) noexcept = delete;
			Health& operator=(const Health&) = delete;
			Health& operator=(Health&&) noexcept = delete;

			virtual void OnNotify(dae::GameObject* pObject, const OBSERVER_EVENTS & event) override;

		protected:

		private:
			std::shared_ptr<dae::GameObject> m_pMessageReceiver;
	};

	class Score final : public Observer
	{
		public:
			Score(const std::shared_ptr<dae::GameObject>& pMessageRecieverP1, const std::shared_ptr<dae::GameObject>& pMessageRecieverP2);
			virtual ~Score() = default;

			Score(const Score&) = delete;
			Score(Score&&) noexcept = delete;
			Score& operator=(const Score&) = delete;
			Score& operator=(Score&&) noexcept = delete;

			virtual void OnNotify(dae::GameObject* pObject, const OBSERVER_EVENTS& event) override;

		protected:

		private:
			int m_Score;
	};
}