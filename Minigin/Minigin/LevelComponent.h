#pragma once
#include "Component.h"

// GLM Includes
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "Observer.h"

namespace Helheim
{
	class GameObject;
}
namespace Helheim
{
	class Scene;
	class Cube;
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
			Cube* GetCubeByIndex(size_t cubeIndex) { return m_pCubes[cubeIndex]; }

		protected:
			virtual void Initialize(Scene* pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			Observer::OBSERVER_EVENTS m_Event;
			glm::vec3 m_CurrentColor;
			glm::vec3 m_StartColor;

			Helheim::TextureComponent* m_pTextureComponent;
			std::vector<Cube*> m_pCubes;

			void Create_AddConnections();
			void AddConnections(size_t cubeToEdit, std::vector<size_t> connectionIDs);
	};
}