#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//#include "Renderer.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Font.h"


#include "GameObject.h"

void dae::ResourceManager::Init(const std::string& dataPath)
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

//std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file) const
//{
//	const auto fullPath = m_DataPath + file;
//	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
//	if (texture == nullptr) 
//	{
//		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
//	}
//	return std::make_shared<Texture2D>(texture);
//}
SDL_Texture* dae::ResourceManager::LoadTexture(const std::string& file, std::shared_ptr<dae::GameObject> pParentObject) const
{
	const auto fullPath = m_DataPath + file;
	//auto texture = IMG_LoadTexture(RenderComponent::GetInstance().GetSDLRenderer(), fullPath.c_str());
	SDL_Texture* texture = IMG_LoadTexture(pParentObject->GetComponent<Helheim::RenderComponent>()->GetSDLRenderer(), fullPath.c_str());
	
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return texture;
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}
