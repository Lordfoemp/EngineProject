#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class GameObject;
}
namespace Helheim
{
	class RenderComponent;
	class TextureComponent;
	class TextComponent final : public Component
	{
		public:
			TextComponent(std::shared_ptr<dae::GameObject>& pParentObject, const std::string& text, std::shared_ptr<dae::Font>& font);
			virtual ~TextComponent() = default;

			TextComponent(const TextComponent&) = delete;
			TextComponent(TextComponent&&) noexcept = delete;
			TextComponent& operator=(const TextComponent&) = delete;
			TextComponent& operator=(TextComponent&&) noexcept = delete;

			void SetFPSText(const std::string& text) 
			{ 
				m_Text = "FPS: " + text; 
				m_Update = true;
			};

		protected:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void FixedUpdate() override;

		private:
			bool m_Update;
			std::string m_Text;
			std::shared_ptr<dae::Font> m_Font;

			std::shared_ptr<Helheim::TextureComponent> m_pTextureComponent;
			std::shared_ptr<Helheim::RenderComponent> m_pRenderComponent;
	};
}