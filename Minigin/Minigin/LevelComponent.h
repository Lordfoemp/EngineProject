#pragma once
#include "Component.h"

namespace Helheim
{
	class Scene;
	class Cube;
	class GameObject;
	class TextureComponent;
	class LevelComponent : public Component
	{			
		public:
			enum class LevelNmr
			{
				Level01,
				Level02,
				Level03
			};
			LevelComponent(Helheim::GameObject* pParentObject, const glm::vec3& color, const std::string& folder, const LevelNmr& levelNmr);
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
			
			std::vector<Cube*> GetCubes() const { return m_pCubes; }
			Cube* GetCubeByIndex(size_t cubeIndex) { return m_pCubes[cubeIndex]; }

			void IncreaseTouchedCubes() { m_TouchedCubes++; }
			int GetNbrOfTouchedCubes() const { return m_TouchedCubes; }

			bool ColorCube(const size_t index);

		protected:
			virtual void Initialize(Scene* pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			int m_TouchedCubes;
			LevelNmr m_LevelNmr;
			Observer::OBSERVER_EVENTS m_Event;
			glm::vec3 m_CurrentColor;
			glm::vec3 m_StartColor;
			std::string m_FolderPath;

			//Helheim::TextureComponent* m_pTextureComponent;
			std::vector<Cube*> m_pCubes;

			void Create_AddConnections();
			void AddConnections(size_t cubeToEdit, std::vector<size_t> connectionIDs);

			bool LevelDone(const LevelNmr& levelNmr) const;
	};
}