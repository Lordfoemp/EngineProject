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
	{
		m_pRenderComponent = std::make_shared<Helheim::RenderComponent>(pParentObject);
		pParentObject->AddComponent(m_pRenderComponent);
	}
	else
		m_pRenderComponent = pParentObject->GetComponent<Helheim::RenderComponent>();

	m_pTransformComponent = pParentObject->GetComponent<Helheim::TransformComponent>();
}
Helheim::TextureComponent::TextureComponent(const std::string& filename, std::shared_ptr<dae::GameObject>& pParentObject)
	                      : Component(pParentObject, true)
						  , m_pTexture(nullptr)
{
	if (!pParentObject->HasComponent<Helheim::RenderComponent>())
	{
		m_pRenderComponent = std::make_shared<Helheim::RenderComponent>(pParentObject);
		pParentObject->AddComponent(m_pRenderComponent);
	}
	else
		m_pRenderComponent = pParentObject->GetComponent<Helheim::RenderComponent>();

	m_pTransformComponent = pParentObject->GetComponent<Helheim::TransformComponent>();

	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename, pParentObject);
}
Helheim::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_pTexture);
}

void Helheim::TextureComponent::Render()
{
	const glm::vec3 position{ m_pTransformComponent->GetPosition() };
	m_pRenderComponent->RenderTexture(m_pTexture, position.x, position.y);
}

void Helheim::TextureComponent::Initialize()
{}
void Helheim::TextureComponent::Update()
{}
void Helheim::TextureComponent::FixedUpdate()
{}