#pragma once
#include "Component.h"

struct SDL_Texture;
namespace Helheim
{
	class TextureComponent : public Component
	{
		public:
			TextureComponent();
			virtual ~TextureComponent() override;

			TextureComponent(const TextureComponent&) = delete;
			TextureComponent(TextureComponent&&) noexcept = delete;
			TextureComponent& operator=(const TextureComponent&) = delete;
			TextureComponent& operator=(TextureComponent&&) noexcept = delete;

		protected:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void Draw() override;

		private:
			SDL_Texture* m_pTexture;
	};
}