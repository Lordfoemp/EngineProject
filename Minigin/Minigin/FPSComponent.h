#pragma once
#include "Component.h"

namespace Helheim
{
	class Font;
	class GameObject;
}
namespace Helheim
{
	class TextComponent;
	class FPSComponent final : public Component
	{
		public:
			FPSComponent(Helheim::GameObject* pParentObject, Font* pFont);
			virtual ~FPSComponent() = default;;

			FPSComponent(const FPSComponent&) = delete;
			FPSComponent(FPSComponent&&) noexcept = delete;
			FPSComponent& operator=(const FPSComponent&) = delete;
			FPSComponent& operator=(FPSComponent&&) noexcept = delete;

			int GetFPS() const { return m_FPS; }

		protected:
			virtual void Initialize() override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			int m_FPS;
			int m_FrameCounter;
			float m_FrameTime;

			Helheim::TextComponent* m_pTextComponent;
	};
}