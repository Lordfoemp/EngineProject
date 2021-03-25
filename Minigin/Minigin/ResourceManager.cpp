#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

#include "Locator.h"

void Helheim::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

SDL_Texture* Helheim::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + file;
	//auto texture = IMG_LoadTexture(RenderComponent::GetInstance().GetSDLRenderer(), fullPath.c_str());
	//SDL_Texture* texture = IMG_LoadTexture(Helheim::Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	SDL_Texture* texture = IMG_LoadTexture(Locator::GetRendererService()->GetSDLRenderer(), fullPath.c_str());

	if (texture == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());

	return texture;
}
//Helheim::Texture2D* Helheim::ResourceManager::LoadTexture(const std::string& file) const
//{
//	const auto fullPath = m_DataPath + file;
//	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
//	if (texture == nullptr) 
//	{
//		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
//	}
//	return new Texture2D(texture);
//}

Helheim::Font* Helheim::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	Helheim::Font* pFontTemp{ new Font(m_DataPath + file, size) };
	return pFontTemp;
}

Mix_Chunk* Helheim::ResourceManager::LoadAudio(const std::string& file) const
{
	std::string path{ m_DataPath + "Sounds/" + file };
	Mix_Chunk* returnChunck{ Mix_LoadWAV(path.c_str()) };
	return returnChunck;
}

Mix_Music* Helheim::ResourceManager::LoadMusic(const std::string& file) const
{
	std::string path{ m_DataPath + "Sounds/" + file };
	Mix_Music* returnMusic{ Mix_LoadMUS(path.c_str()) };
	return returnMusic;
}
