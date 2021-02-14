#include "MiniginPCH.h"
#include "RenderComponent.h"

// External Includes
#include <SDL.h>

// dae Includes
#include "Renderer.h"

Helheim::RenderComponent::RenderComponent(std::shared_ptr<dae::GameObject>& pParentObject)
						 : Component(pParentObject, false)
						 , m_pRenderer(dae::Renderer::GetInstance().GetSDLRenderer())
{}
Helheim::RenderComponent::~RenderComponent()
{}

void Helheim::RenderComponent::Initialize()
{}
void Helheim::RenderComponent::Update()
{}

void Helheim::RenderComponent::RenderTexture(SDL_Texture* const texture, float x, float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(m_pRenderer, texture, nullptr, &dst);
}
void Helheim::RenderComponent::RenderTexture(SDL_Texture* const texture, float x, float y, float width, float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(m_pRenderer, texture, nullptr, &dst);
}