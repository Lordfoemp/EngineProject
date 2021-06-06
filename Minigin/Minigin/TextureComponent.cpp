#include "MiniginPCH.h"
#include "TextureComponent.h"

// External Includes
//#include <SDL.h>

// dae Includes
#include "ResourceManager.h"

// Helheim Includes
#include "RenderComponent.h"
#include "TransformComponent.h"
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
Helheim::TextureComponent::TextureComponent(const std::string& filename, const std::string& folderpath, Helheim::GameObject* pParentObject)
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

	m_pTexture = Locator::GetResourceService()->LoadTexture(filename, folderpath);

	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_Width, &m_Height);
}
Helheim::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_pTexture);
}

void Helheim::TextureComponent::Initialize(Scene*) // pParentScene
{}
void Helheim::TextureComponent::PostInitialize(Scene*)//pParentScene
{
}
void Helheim::TextureComponent::Update(const float)
{}
void Helheim::TextureComponent::FixedUpdate(const float)
{}
void Helheim::TextureComponent::Render()
{
	const glm::vec3 position{ m_pTransformComponent->GetPosition() };
	m_pRenderComponent->RenderTexture(m_pTexture, position, { m_Position_Left, 0, 0}, (float)m_Width, (float)m_Height);
}

void Helheim::TextureComponent::UpdateRenderSettings(const int width, const int height, const int positionLeft)
{
	m_Width = width;
	m_Height = height;
	m_Position_Left = positionLeft;
}