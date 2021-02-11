#pragma once
#include "Component.h"

namespace Helheim
{
	class TextComponent : public Component
	{
		public:
			TextComponent();
			virtual ~TextComponent() override = default;

			TextComponent(const TextComponent&) = delete;
			TextComponent(TextComponent&&) noexcept = delete;
			TextComponent& operator=(const TextComponent&) = delete;
			TextComponent& operator=(TextComponent&&) noexcept = delete;

		protected:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void Draw() override;

		private:
			std::string m_Text;
	};
}