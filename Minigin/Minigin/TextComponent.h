#pragma once
#include "Component.h"

namespace Helheim
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
			TextComponent(Helheim::GameObject* pParentObject, const std::string& text, Helheim::Font* font);
			virtual ~TextComponent();

			TextComponent(const TextComponent&) = delete;
			TextComponent(TextComponent&&) noexcept = delete;
			TextComponent& operator=(const TextComponent&) = delete;
			TextComponent& operator=(TextComponent&&) noexcept = delete;

			void SetFPSText(const std::string& text) 
			{ 
				m_Text = "FPS: " + text; 
				m_Update = true;
			};
			void SetHealthText(const std::string& text)
			{
				m_Text = "Lives left: " + text;
				m_Update = true;
			};
			void SetScoreText(const std::string& text)
			{
				m_Text = "Score: " + text;
				m_Update = true;
			};

		protected:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void FixedUpdate() override;

		private:
			bool m_Update;
			std::string m_Text;
			Helheim::Font* m_pFont;

			Helheim::TextureComponent* m_pTextureComponent;
			Helheim::RenderComponent* m_pRenderComponent;
	};
}