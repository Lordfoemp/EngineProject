#include "MiniginPCH.h"
#include "Component.h"

Helheim::Component::Component(dae::GameObject* pParentObject, const bool canRenderComponent)
				   : m_pParentObject(pParentObject)
				   , m_CanRenderComponent(canRenderComponent)
{}

void Helheim::Component::NotifyObservers(dae::GameObject* pParentObject, const Observer::OBSERVER_EVENTS& observerEvent)
{
	const size_t observersAmount{ m_pObservers.size() };
	for (size_t i{}; i < observersAmount; i++)
	{
		m_pObservers[i]->OnNotify(pParentObject, observerEvent);
	}
}