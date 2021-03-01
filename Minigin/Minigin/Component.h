#pragma once
#include "Observer.h"

namespace dae
{ 
	class GameObject; 
}
namespace Helheim
{
	class Component
	{
		public:
			Component(dae::GameObject* pParentObject, const bool canRenderComponent);
			virtual ~Component() = default;

			Component(const Component&) = delete;
			Component(Component&&) noexcept = delete;
			Component& operator=(const Component&) = delete;
			Component& operator=(Component&&) noexcept = delete;

			virtual void Initialize() = 0;
			virtual void Update() = 0;
			virtual void FixedUpdate() = 0;
			
			//void AddObserver(std::shared_ptr<Observer>(pObserver)) { m_pObservers.push_back(pObserver); }
			void AddObserver(const std::shared_ptr<Observer>& pObserver) { m_pObservers.push_back(pObserver); }
			//void RemoveObserver(std::shared_ptr<Observer>(pObserver)) 
			//{ m_pObservers.erase(std::find(m_pObservers.begin(), m_pObservers.end(),pObserver)); }

			bool GetCanRenderComponent() const { return m_CanRenderComponent; }
			void NotifyObservers(dae::GameObject* pParentObject, const Observer::OBSERVER_EVENTS& observerEvent);

		protected:
			dae::GameObject* m_pParentObject;
			dae::GameObject* GetParentObject() const { return m_pParentObject; }
			
			std::vector<std::shared_ptr<Observer>> m_pObservers;

		private:
			bool m_CanRenderComponent;
	};
}