#include "MiniginPCH.h"
#include "TextComponent.h"

// External Includes
#include <SDL.h>
#include <SDL_ttf.h>

// dae Includes
#include "GameObject.h"
#include "Font.h"

// Helheim Includes
#include "TextureComponent.h"
#include "RenderComponent.h"

Helheim::TextComponent::TextComponent(std::shared_ptr<dae::GameObject>& pParentObject, const std::string& text, std::shared_ptr<dae::Font>& font)
					   : Component(pParentObject, false)
					   , m_Update(true)
					   , m_Text(text)
					   , m_Font(font)
{
	if (!pParentObject->HasComponent<Helheim::TextureComponent>())
	{
		m_pTextureComponent = std::make_shared<Helheim::TextureComponent>(pParentObject);
		pParentObject->AddComponent(m_pTextureComponent);
	}
	else
		m_pTextureComponent = pParentObject->GetComponent<Helheim::TextureComponent>();

	m_pRenderComponent = pParentObject->GetComponent<Helheim::RenderComponent>();
}

void Helheim::TextComponent::Initialize()
{}
void Helheim::TextComponent::Update()
{
	if (m_Update)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

		auto pTexture = SDL_CreateTextureFromSurface(m_pRenderComponent->GetSDLRenderer(), surf);
		if (pTexture == nullptr)
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		m_pTextureComponent->SetSDLTexture(pTexture);
		
		SDL_FreeSurface(surf);
		m_Update = false;
	}
}
void Helheim::TextComponent::FixedUpdate()
{}