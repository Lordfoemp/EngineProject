#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* Helheim::Font::GetFont() const 
{
	return m_Font;
}

Helheim::Font::Font(const std::string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_Font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

Helheim::Font::~Font()
{
	TTF_CloseFont(m_Font);
}
