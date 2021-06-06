#pragma once
#pragma once
#include <Scene.h>

namespace Helheim
{
	class GameObject;
	class TextureComponent;
	class MainMenu final : public Scene
	{		
		public:
			MainMenu(const int windowWidth, const int windowHeight, const bool isActive);
			virtual ~MainMenu() = default;

			MainMenu(const MainMenu&) = delete;
			MainMenu(MainMenu&&) noexcept = delete;
			MainMenu& operator=(const MainMenu&) = delete;
			MainMenu& operator=(MainMenu&&) noexcept = delete;

			virtual void Initialize() override;
			virtual void PostInitialize() override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;
			virtual void LateUpdate() override;
			virtual void Render() const override;					

		protected:

		private:
			GameObject* m_pMenuGO;
			TextureComponent* m_pTextureComponent_Base;
			TextureComponent* m_pTextureComponent_Play_Pressed;
			TextureComponent* m_pTextureComponent_Controls_Pressed;
			TextureComponent* m_pTextureComponent_Quit_Pressed;
			
			void InitializeImage();
			void InitializeButtons();
			void InitializeInputs();

			void DisableAllImages();

			bool IsInsideButton(const glm::vec2& currMousePos, const Button& button);
	};
}