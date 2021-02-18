#include "MiniginPCH.h"
#include "GameObject.h"

#include "Component.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

dae::GameObject::GameObject(const glm::vec3& position)
{
	std::shared_ptr<Helheim::TransformComponent> pTransformComponent{ std::make_shared<Helheim::TransformComponent>(std::shared_ptr<dae::GameObject>(this), position) };
	AddComponent(pTransformComponent);
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto& comp : m_pComponents) //auto comp : m_pComponents
	{
		comp->Update();
	}
	for (auto& comp : m_pComponents) //auto comp : m_pComponents
	{
		comp->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (auto& comp : m_pComponents)
	{
		if (comp->GetCanRenderComponent())
		{
			const type_info& ti = typeid(comp);
			if (ti.before(typeid(Helheim::TextureComponent)))
			{
				auto texture = std::dynamic_pointer_cast<Helheim::TextureComponent>(comp);
				texture->Render();
			}
		}			
	}
}