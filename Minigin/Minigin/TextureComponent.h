#pragma once
#include "Component.h"

struct SDL_Texture;
struct SDL_Window;
namespace Helheim
{
	class Scene;
	class GameObject;
	class RenderComponent;
	class TransformComponent;
	class TextureComponent final : public Component
	{
		public:
			TextureComponent(Helheim::GameObject* pParentObject);
			TextureComponent(const std::string& filename, const std::string& folderpath, Helheim::GameObject* pParentObject);
			virtual ~TextureComponent();

			TextureComponent(const TextureComponent&) = delete;
			TextureComponent(TextureComponent&&) noexcept = delete;
			TextureComponent& operator=(const TextureComponent&) = delete;
			TextureComponent& operator=(TextureComponent&&) noexcept = delete;

			void SetSDLTexture(SDL_Texture* pTexture) { m_pTexture = pTexture; }
			SDL_Texture* GetSDLTexture() const { return m_pTexture; }

			void Render();

			void UpdateRenderSettings(const int width, const int height, const int positionLeft);

			int GetLeftPosition() const { return m_Position_Left; }

		protected:
			virtual void Initialize(Scene* pParentScene) override;
			virtual void PostInitialize(Scene* pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			int m_Width,
				m_Height;
			int m_Position_Left;
			SDL_Texture* m_pTexture;
			Helheim::RenderComponent* m_pRenderComponent;
			Helheim::TransformComponent* m_pTransformComponent;
	};
}