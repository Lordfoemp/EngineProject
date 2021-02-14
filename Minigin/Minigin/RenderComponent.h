#pragma once
#include "Component.h"

// External Includes
#include <SDL.h>

struct SDL_Renderer;
struct SDL_Window;
namespace Helheim
{
	class RenderComponent final : public Component
	{
		public:
			RenderComponent(std::shared_ptr<dae::GameObject>& pParentObject);
			virtual ~RenderComponent();

			RenderComponent(const RenderComponent&) = delete;
			RenderComponent(RenderComponent&&) noexcept = delete;
			RenderComponent& operator=(const RenderComponent&) = delete;
			RenderComponent& operator=(RenderComponent&&) noexcept = delete;

			void RenderTexture(SDL_Texture* const texture, float x, float y) const;
			void RenderTexture(SDL_Texture* const texture, float x, float y, float width, float height) const;

			SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

		protected:
			virtual void Initialize() override;
			virtual void Update() override;

		private:
			SDL_Renderer* m_pRenderer;	// Managed by dae::Renderer
	};
}