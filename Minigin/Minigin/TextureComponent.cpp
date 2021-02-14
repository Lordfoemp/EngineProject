#include "MiniginPCH.h"
#include "TextureComponent.h"

// External Includes
#include <SDL.h>

// dae Includes
#include "ResourceManager.h"

// Helheim Includes
#include "RenderComponent.h"

Helheim::TextureComponent::TextureComponent(std::shared_ptr<dae::GameObject>& pParentObject)
						  : Component(pParentObject, true)
						  , m_pTexture(nullptr)
{
	if (!pParentObject->HasComponent<Helheim::RenderComponent>())
		pParentObject->AddComponent(std::make_shared<Helheim::RenderComponent>(pParentObject));
}
Helheim::TextureComponent::TextureComponent(const std::string& filename, std::shared_ptr<dae::GameObject>& pParentObject)
	                      : Component(pParentObject, true)
						  , m_pTexture(nullptr)
{
	if (!pParentObject->HasComponent<Helheim::RenderComponent>())
		pParentObject->AddComponent(std::make_shared<Helheim::RenderComponent>(pParentObject));
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename, pParentObject);
}
Helheim::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_pTexture);
}

void Helheim::TextureComponent::Render()
{
	std::shared_ptr<Helheim::TransformComponent> pTransformComponent{ m_pParentObject->GetComponent<Helheim::TransformComponent>() };
	std::shared_ptr<Helheim::RenderComponent> pRenderComponent{ m_pParentObject->GetComponent<Helheim::RenderComponent>() };
	
	const glm::vec3 position{ pTransformComponent->GetPosition() };
	pRenderComponent->RenderTexture(m_pTexture, position.x, position.y);
}

void Helheim::TextureComponent::Initialize()
{}
void Helheim::TextureComponent::Update()
{}