#include "MiniginPCH.h"
#include "RenderComponent.h"

// External Includes
#include <SDL.h>

// dae Includes
#include "Renderer.h"
#include "GameObject.h"

// Helheim includes
#include "TransformComponent.h"

Helheim::RenderComponent::RenderComponent(std::shared_ptr<dae::GameObject>& pParentObject)
						 : Component(pParentObject, false)
						 , m_pRenderer(dae::Renderer::GetInstance().GetSDLRenderer())
						 , m_pTransformComponent(nullptr)
{
	m_pTransformComponent = pParentObject->GetComponent<TransformComponent>();
}
Helheim::RenderComponent::~RenderComponent()
{}

void Helheim::RenderComponent::Initialize()
{}
void Helheim::RenderComponent::Update()
{}
void Helheim::RenderComponent::FixedUpdate()
{}

void Helheim::RenderComponent::RenderTexture(SDL_Texture* const texture, float x, float y) const
{	
	const glm::vec3 scale{ m_pTransformComponent->GetScale() };

	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);

	// Adjust the image to the scale
	dst.w = (int)(dst.w * scale.x);
	dst.h = (int)(dst.h * scale.y);

	SDL_RenderCopy(m_pRenderer, texture, nullptr, &dst);
}
void Helheim::RenderComponent::RenderTexture(SDL_Texture* const texture, float x, float y, float width, float height) const
{
	const glm::vec3 scale{ m_pTransformComponent->GetScale() };

	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(scale.x * width);
	dst.h = static_cast<int>(scale.y * height);

	SDL_RenderCopy(m_pRenderer, texture, nullptr, &dst);
}