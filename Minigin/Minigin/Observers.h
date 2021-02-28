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
			Health(const std::shared_ptr<dae::GameObject>& pMessageReciever);
			virtual ~Health() = default;

			Health(const Health&) = delete;
			Health(Health&&) noexcept = delete;
			Health& operator=(const Health&) = delete;
			Health& operator=(Health&&) noexcept = delete;

			virtual void OnNotify(std::shared_ptr<dae::GameObject>& pObject, const OBSERVER_EVENTS & event) override;

		protected:

		private:
			std::shared_ptr<dae::GameObject> m_pMessageReceiver;
	};
}