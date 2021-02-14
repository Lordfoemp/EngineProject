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
	auto rComp = GetComponent<Helheim::RenderComponent>();
	for (auto& comp : m_pComponents) //auto comp : m_pComponents
	{
		comp->Update();
	}
}

void dae::GameObject::Render() const
{
	//auto rcomp{ GetComponent<Helheim::RenderComponent>() };
	//SDL_RenderClear(rcomp->GetSDLRenderer());
	//auto tComp{ GetComponent<Helheim::TextureComponent>() };
	//if (rcomp)
	//{
	//	rcomp->RenderTexture(*tComp, 0, 0);
	//}

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
			//else if (ti.before(typeid(Helheim::TextureComponent)))
			//{
			//	auto texture = std::dynamic_pointer_cast<Helheim::TextureComponent>(comp);
			//	texture->Render();
			//}
		}			
	}
	//SDL_RenderPresent(rcomp->GetSDLRenderer());
}
