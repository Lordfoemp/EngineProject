#include "MiniginPCH.h"
#include "GameObject.h"

#include "Component.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

Helheim::GameObject::GameObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	std::shared_ptr<Helheim::TransformComponent> pTransformComponent{ std::make_shared<Helheim::TransformComponent>(this, position, rotation, scale) };
	AddComponent(pTransformComponent);
}

void Helheim::GameObject::Update()
{
	for (std::shared_ptr<Helheim::Component>& comp : m_pComponents) //auto comp : m_pComponents
		comp->Update();
}
void Helheim::GameObject::FixedUpdate()
{
	for (std::shared_ptr<Helheim::Component>& comp : m_pComponents) //auto comp : m_pComponents
		comp->FixedUpdate();
}

void Helheim::GameObject::Render() const
{
	for (const std::shared_ptr<Helheim::Component>& comp : m_pComponents)
	{
		if (comp->GetCanRenderComponent())
		{
			const type_info& ti = typeid(comp);
			if (ti.before(typeid(Helheim::TextureComponent)))
			{
				std::shared_ptr<Helheim::TextureComponent> texture = std::dynamic_pointer_cast<Helheim::TextureComponent>(comp);
				if (texture)
					texture->Render();
			}
		}			
	}
}