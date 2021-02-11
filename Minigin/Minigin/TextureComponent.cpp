#include "MiniginPCH.h"
#include "TextureComponent.h"

#include <SDL.h>

Helheim::TextureComponent::TextureComponent()
						  : m_pTexture( nullptr )
{}
Helheim::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_pTexture);
}

void Helheim::TextureComponent::Initialize()
{}
void Helheim::TextureComponent::Update()
{}
void Helheim::TextureComponent::Draw()
{}