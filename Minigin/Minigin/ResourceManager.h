#pragma once
#include "Singleton.h"
#include <SDL_mixer.h>
struct SDL_Texture;
namespace Helheim
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		public:
			ResourceManager() = default;
			void Init(const std::string& data);
			//Texture2D* LoadTexture(const std::string& file) const;
			SDL_Texture* LoadTexture(const std::string& file) const;
			Font* LoadFont(const std::string& file, unsigned int size) const;
			Mix_Chunk* LoadAudio(const std::string& file) const;
			Mix_Music* LoadMusic(const std::string& file) const;
		private:
			friend class Singleton<ResourceManager>;
			
			std::string m_DataPath;
	};
}
