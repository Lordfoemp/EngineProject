#pragma once
#include "Component.h"

// GLM Includes
#include "glm/vec3.hpp"

#include "Observer.h"

namespace Helheim
{
	class GameObject;
}
namespace Helheim
{
	//class Observer;
	class TextureComponent;
	class LevelComponent : public Component
	{
		public:
			LevelComponent(Helheim::GameObject* pParentObject, const glm::vec3& color);
			virtual ~LevelComponent() = default;;

			LevelComponent(const LevelComponent&) = delete;
			LevelComponent(LevelComponent&&) noexcept = delete;
			LevelComponent& operator=(const LevelComponent&) = delete;
			LevelComponent& operator=(LevelComponent&&) noexcept = delete;

			void ColorChange(const Observer::OBSERVER_EVENTS& event)
			{ 
				m_CurrentColor = glm::vec3(0, 1, 0); 
				m_Event = event;
			}
			void ResetChange() { m_CurrentColor = glm::vec3(1, 0, 0); }

		protected:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void FixedUpdate() override;

		private:
			Observer::OBSERVER_EVENTS m_Event;
			glm::vec3 m_CurrentColor;
			glm::vec3 m_StartColor;

			std::shared_ptr<Helheim::TextureComponent> m_pTextureComponent;
	};
}