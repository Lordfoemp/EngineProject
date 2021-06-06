#pragma once
#pragma once
#include <Scene.h>

namespace Helheim
{
	class GameObject;
	class TextureComponent;
	class ControlsMenu final : public Scene
	{
		public:
			ControlsMenu(const int windowWidth, const int windowHeight, const bool isActive);
			virtual ~ControlsMenu() = default;

			ControlsMenu(const ControlsMenu&) = delete;
			ControlsMenu(ControlsMenu&&) noexcept = delete;
			ControlsMenu& operator=(const ControlsMenu&) = delete;
			ControlsMenu& operator=(ControlsMenu&&) noexcept = delete;

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
			TextureComponent* m_pTextureComponent_Back_Pressed;

			void InitializeImage();
			void InitializeButtons();
			void InitializeInputs();

			void DisableAllImages();

			bool IsInsideButton(const glm::vec2& currMousePos, const Button& button);
	};
}