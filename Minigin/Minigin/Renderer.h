#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Helheim
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		public:
			Renderer();
			~Renderer();

			Renderer(const Renderer&) = delete;
			Renderer(Renderer&&) = delete;
			Renderer& operator= (const Renderer&) = delete;
			Renderer& operator= (const Renderer&&) = delete;

			void Init(SDL_Window* window);
			void Render() const;

			//void RenderTexture(const Texture2D& texture, float x, float y) const;
			//void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

			SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }
			void RenderUI() const;

		private:
			bool m_ShowDemoWindow;
			bool m_ShowControlWindow;
			SDL_Window* m_pWindow;
			SDL_Renderer* m_pRenderer;
	};
}

