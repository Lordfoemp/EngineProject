#include "MiniginPCH.h"
#include "TextureComponent.h"

// External Includes
#include <SDL.h>

// dae Includes
#include "ResourceManager.h"

// Helheim Includes
#include "RenderComponent.h"

#include "GameObject.h"

Helheim::TextureComponent::TextureComponent(Helheim::GameObject* pParentObject)
						  : Component(pParentObject, true)
						  , m_pTexture(nullptr)
						  , m_Width()
						  , m_Height()
{
	if (!pParentObject->HasComponent<Helheim::RenderComponent>())
	{
		m_pRenderComponent = new Helheim::RenderComponent(pParentObject);
		pParentObject->AddComponent(m_pRenderComponent);
	}
	else
		m_pRenderComponent = pParentObject->GetComponent<Helheim::RenderComponent>();

	m_pTransformComponent = pParentObject->GetComponent<Helheim::TransformComponent>();
}
Helheim::TextureComponent::TextureComponent(const std::string& filename, Helheim::GameObject* pParentObject)
	                      : Component(pParentObject, true)
						  , m_pTexture(nullptr)
{
	if (!pParentObject->HasComponent<Helheim::RenderComponent>())
	{
		m_pRenderComponent = new Helheim::RenderComponent(pParentObject);
		pParentObject->AddComponent(m_pRenderComponent);
	}
	else
		m_pRenderComponent = pParentObject->GetComponent<Helheim::RenderComponent>();

	m_pTransformComponent = pParentObject->GetComponent<Helheim::TransformComponent>();

	//m_pTexture = Helheim::ResourceManager::GetInstance().LoadTexture(filename);
	m_pTexture = Locator::GetResourceService()->LoadTexture(filename);

	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_Width, &m_Height);
}
Helheim::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_pTexture);
}

void Helheim::TextureComponent::Render()
{
	const glm::vec3 position{ m_pTransformComponent->GetPosition() };
	m_pRenderComponent->RenderTexture(m_pTexture, position.x, position.y);
	//m_pRenderComponent->RenderTexture(m_pTexture, position.x, position.y, (float)m_Width, (float)m_Height);
}

void Helheim::TextureComponent::Initialize()
{}
void Helheim::TextureComponent::Update()
{}
void Helheim::TextureComponent::FixedUpdate()
{}