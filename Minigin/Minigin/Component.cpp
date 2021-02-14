#include "MiniginPCH.h"
#include "Component.h"

Helheim::Component::Component(std::shared_ptr<dae::GameObject>& pParentObject, const bool canRenderComponent)
				   : m_pParentObject(pParentObject)
				   , m_CanRenderComponent(canRenderComponent)
{}