#pragma once
#include "Component.h"

namespace Helheim
{
	class FontComponent : public Component
	{
		public:
			FontComponent();
			virtual ~FontComponent() override = default;

			FontComponent(const FontComponent&) = delete;
			FontComponent(FontComponent&&) noexcept = delete;
			FontComponent& operator=(const FontComponent&) = delete;
			FontComponent& operator=(FontComponent&&) noexcept = delete;

		protected:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void Draw() override;

		private:
			
	};
}