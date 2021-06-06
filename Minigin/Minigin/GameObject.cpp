#include "MiniginPCH.h"
#include "GameObject.h"

#include "Component.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

Helheim::GameObject::GameObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	Helheim::TransformComponent* pTransformComponent{ new Helheim::TransformComponent(this, position, rotation, scale) };
	AddComponent(pTransformComponent);
}
Helheim::GameObject::~GameObject()
{
	for (Helheim::Component* pComp : m_pComponents)
		DELETE_POINTER(pComp);
}

void Helheim::GameObject::Initialize()
{
	for (Helheim::Component* comp : m_pComponents) 
		comp->Initialize(m_pParentScene);
}
void Helheim::GameObject::PostInitialize()
{
	for (Helheim::Component* comp : m_pComponents)
		comp->PostInitialize(m_pParentScene);
}
void Helheim::GameObject::Update(const float elapsedSec)
{
	for (Helheim::Component* comp : m_pComponents) //auto comp : m_pComponents
		comp->Update(elapsedSec);
}
void Helheim::GameObject::FixedUpdate(const float timeEachUpdate)
{
	for (Helheim::Component* comp : m_pComponents) //auto comp : m_pComponents
		comp->FixedUpdate(timeEachUpdate);
}

void Helheim::GameObject::Render() const
{
	for (Helheim::Component* comp : m_pComponents)
	{
		if (comp->CanRenderComponent())
		{
			Helheim::TextureComponent* texture = dynamic_cast<Helheim::TextureComponent*>(comp);
			if (texture)
				texture->Render();
		}			
	}
}