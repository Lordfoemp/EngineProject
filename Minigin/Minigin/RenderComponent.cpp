#include "MiniginPCH.h"
#include "RenderComponent.h"

// External Includes
#include <SDL.h>

// dae Includes
#include "Renderer.h"
#include "GameObject.h"

// Helheim includes
#include "TransformComponent.h"

Helheim::RenderComponent::RenderComponent(Helheim::GameObject* pParentObject)
						 : Component(pParentObject, false)
						 , m_pRenderer(Locator::GetRendererService()->GetSDLRenderer())
						 , m_pTransformComponent(nullptr)
{
	m_pTransformComponent = pParentObject->GetComponent<TransformComponent>();
}

void Helheim::RenderComponent::Initialize()
{}
void Helheim::RenderComponent::Update(const float)
{}
void Helheim::RenderComponent::FixedUpdate(const float)
{}

void Helheim::RenderComponent::RenderTexture(SDL_Texture* const texture, float x, float y) const
{	
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);

	const glm::vec3 scale{ m_pTransformComponent->GetScale() };

	// Get the complete texture size
	// [0, 0]        [0, w]
	//   +-------------+
	//   |             |
	//   |             |
	//   +-------------+
	// [h, 0]        [h, w]
	SDL_Rect src;
	src.x = static_cast<int>(31);
	src.y = static_cast<int>(160);
	//SDL_QueryTexture(texture, nullptr, nullptr, &src.w, &src.h);
	//src.w = 34;
	//src.h = 32;
	// Define the size of the current sprite to render from the sprite sheet
	// x, y: The position in the game screen where to render
	// w, h: The amount of pixels to render from the sprite sheet
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	dst.w = (int)(dst.w * scale.x);
	dst.h = (int)(dst.h * scale.y);
	SDL_RenderCopy(m_pRenderer, texture, nullptr, &dst);
}
void Helheim::RenderComponent::RenderTexture(SDL_Texture* const texture, float x, float y, float width, float height) const
{
	UNREFERENCED_PARAMETER(width);
	UNREFERENCED_PARAMETER(height);

	const glm::vec3 scale{ m_pTransformComponent->GetScale() };

	//SDL_Rect dst;
	//dst.x = static_cast<int>(x);
	//dst.y = static_cast<int>(y);
	//dst.w = static_cast<int>(scale.x * width);
	//dst.h = static_cast<int>(scale.y * height);

	SDL_Rect src;
	src.x = static_cast<int>(31);
	src.y = static_cast<int>(160);
	src.w = (int)width;
	src.h = (int)height;
	// Define the size of the current sprite to render from the sprite sheet
	// x, y: The position in the game screen where to render
	// w, h: The amount of pixels to render from the sprite sheet
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = (int)(src.w);
	dst.h = (int)(src.h);
	SDL_RenderCopy(m_pRenderer, texture, nullptr, &dst);
}