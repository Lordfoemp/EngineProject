#pragma once
#include "Component.h"

namespace Helheim
{
	class Scene;
	class Font;
	class GameObject;
	class TextComponent;
	class Observer;
	class HealthComponent final : public Component
	{
		public:
			HealthComponent(Helheim::GameObject* pParentObject, const int maxHealth, const int maxLives);
			virtual ~HealthComponent() = default;;

			HealthComponent(const HealthComponent&) = delete;
			HealthComponent(HealthComponent&&) noexcept = delete;
			HealthComponent& operator=(const HealthComponent&) = delete;
			HealthComponent& operator=(HealthComponent&&) noexcept = delete;
			
			void IncreaseHealth(const int& increase) { m_CurrentHealth += increase; }
			void IncreaseLives(const int& increase) { m_Lives += increase; }
			void DecreaseHealth(const int& decrease) { m_CurrentHealth -= decrease; }
			void DecreaseLives(const int& decrease) { m_Lives -= decrease; }
			int GetHealth() const { return m_CurrentHealth; }
			int GetLives() const { return m_Lives; }

			void Die(const Observer::OBSERVER_EVENTS& event) 
			{
				m_CurrentHealth = 0; 
				m_Event = event;
			}

		protected:
			virtual void Initialize(Scene* pParentScene) override;
			virtual void PostInitialize(Scene* pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			Observer::OBSERVER_EVENTS m_Event;

			int m_Lives;
			int m_CurrentHealth;
			int m_StartHealth;
	};
}