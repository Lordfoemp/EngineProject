#pragma once
#include "Component.h"

struct SDL_Texture;
struct SDL_Window;
namespace Helheim
{
	class GameObject;
}
namespace Helheim
{
	class RenderComponent;
	class TransformComponent;
	class TextureComponent final : public Component
	{
		public:
			TextureComponent(Helheim::GameObject* pParentObject);
			TextureComponent(const std::string& filename, Helheim::GameObject* pParentObject);
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
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			int m_Width;
			int m_Height;
			SDL_Texture* m_pTexture;
			Helheim::RenderComponent* m_pRenderComponent;
			Helheim::TransformComponent* m_pTransformComponent;
	};
}