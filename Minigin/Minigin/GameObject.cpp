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

void Helheim::GameObject::Update()
{
	for (Helheim::Component* comp : m_pComponents) //auto comp : m_pComponents
		comp->Update();
}
void Helheim::GameObject::FixedUpdate()
{
	for (Helheim::Component* comp : m_pComponents) //auto comp : m_pComponents
		comp->FixedUpdate();
}

void Helheim::GameObject::Render() const
{
	for (Helheim::Component* comp : m_pComponents)
	{
		if (comp->CanRenderComponent())
		{
			//const type_info& ti = typeid(comp);
			//if (ti.before(typeid(Helheim::TextureComponent)))
			//{
			//	Helheim::TextureComponent* texture = dynamic_cast<Helheim::TextureComponent*>(comp);
			//	if (texture)
			//		texture->Render();
			//}

			Helheim::TextureComponent* texture = dynamic_cast<Helheim::TextureComponent*>(comp);
			if (texture)
				texture->Render();
		}			
	}
}