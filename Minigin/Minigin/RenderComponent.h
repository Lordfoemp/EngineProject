#pragma once
#include "Component.h"
//#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
namespace Helheim
{
	class Scene;
	class TransformComponent;
	class RenderComponent final : public Component
	{
		public:
			RenderComponent(Helheim::GameObject* pParentObject);
			virtual ~RenderComponent() = default;;

			RenderComponent(const RenderComponent&) = delete;
			RenderComponent(RenderComponent&&) noexcept = delete;
			RenderComponent& operator=(const RenderComponent&) = delete;
			RenderComponent& operator=(RenderComponent&&) noexcept = delete;

			void RenderTexture(SDL_Texture* const texture, float x, float y) const;
			void RenderTexture(SDL_Texture* const texture, float x, float y, float width, float height) const;

			SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

		protected:
			virtual void Initialize(Scene* pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			Helheim::TransformComponent* m_pTransformComponent;
			SDL_Renderer* m_pRenderer;	// Managed by dae::Renderer
	};
}