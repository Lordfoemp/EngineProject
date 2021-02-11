#pragma once
#include "Component.h"

namespace Helheim
{
	class RenderComponent : public Component
	{
		public:
			RenderComponent();
			virtual ~RenderComponent() override = default;

			RenderComponent(const RenderComponent&) = delete;
			RenderComponent(RenderComponent&&) noexcept = delete;
			RenderComponent& operator=(const RenderComponent&) = delete;
			RenderComponent& operator=(RenderComponent&&) noexcept = delete;

		protected:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void Draw() override;

		private:

	};
}