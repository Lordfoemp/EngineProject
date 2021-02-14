#pragma once
#include "Component.h"

struct SDL_Texture;
struct SDL_Window;
namespace dae
{
	class GameObject;
}
namespace Helheim
{
	class TextureComponent final : public Component
	{
		public:
			TextureComponent(std::shared_ptr<dae::GameObject>& pParentObject);
			TextureComponent(const std::string& filename, std::shared_ptr<dae::GameObject>& pParentObject);
			virtual ~TextureComponent();

			TextureComponent(const TextureComponent&) = delete;
			TextureComponent(TextureComponent&&) noexcept = delete;
			TextureComponent& operator=(const TextureComponent&) = delete;
			TextureComponent& operator=(TextureComponent&&) noexcept = delete;

			void SetSDLTexture(SDL_Texture* pTexture) { m_pTexture = pTexture; }
			SDL_Texture* GetSDLTexture() const { return m_pTexture; }

			void Render();

		protected:
			virtual void Initialize() override;
			virtual void Update() override;

		private:
			SDL_Texture* m_pTexture;
	};
}