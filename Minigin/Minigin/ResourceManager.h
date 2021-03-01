#pragma once
#include "Singleton.h"
#include "GameObject.h"

struct SDL_Texture;
namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		public:
			ResourceManager() = default;
			void Init(const std::string& data);
			//std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
			SDL_Texture* LoadTexture(const std::string& file) const;
			std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		private:
			friend class Singleton<ResourceManager>;
			
			std::string m_DataPath;
	};
}
