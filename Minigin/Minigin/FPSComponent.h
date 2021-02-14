#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class GameObject;
}
namespace Helheim
{
	class FPSComponent final : public Component
	{
		public:
			FPSComponent(std::shared_ptr<dae::GameObject>& pParentObject, std::shared_ptr<dae::Font> pFont);
			virtual ~FPSComponent() = default;

			FPSComponent(const FPSComponent&) = delete;
			FPSComponent(FPSComponent&&) noexcept = delete;
			FPSComponent& operator=(const FPSComponent&) = delete;
			FPSComponent& operator=(FPSComponent&&) noexcept = delete;

			int GetFPS() const { return m_FPS; }

		protected:
			virtual void Initialize() override;
			virtual void Update() override;

		private:
			int m_FPS;
			int m_FrameCounter;
			float m_FrameTime;
	};
}


