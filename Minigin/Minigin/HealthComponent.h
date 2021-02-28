#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class GameObject;
}
namespace Helheim
{
	class TextComponent;
	class Observer;
	class HealthComponent final : public Component
	{
		public:
			HealthComponent(std::shared_ptr<dae::GameObject>& pParentObject, const int maxHealth, const int maxLives);
			virtual ~HealthComponent() = default;

			HealthComponent(const HealthComponent&) = delete;
			HealthComponent(HealthComponent&&) noexcept = delete;
			HealthComponent& operator=(const HealthComponent&) = delete;
			HealthComponent& operator=(HealthComponent&&) noexcept = delete;
			
			void IncreaseHealth(const int& increase) { m_Health += increase; }
			void IncreaseLives(const int& increase) { m_Health += increase; }
			void DecreaseHealth(const int& decrease) { m_Health -= decrease; }
			void DecreaseLives(const int& decrease) { m_Health -= decrease; }
			int GetHealth() const { return m_Health; }
			int GetLives() const { return m_Lives; }

		protected:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void FixedUpdate() override;

		private:
			int m_Lives;
			int m_Health;
			//std::shared_ptr<Helheim::TextComponent> m_pTextComponent;

			void NotifyObservers();
	};
}