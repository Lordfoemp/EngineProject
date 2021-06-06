#pragma once
#include "Component.h"

namespace Helheim
{
	class Cube;
	class Disc;
	class Scene;
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
			virtual ~LevelComponent();

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
			
			std::vector<GameObject*> GetCubes() const { return m_pCubes; }
			std::vector<GameObject*> GetDiscs() const { return m_pDiscs; }
			GameObject* GetCubeByIndex(size_t cubeIndex) { return m_pCubes[cubeIndex]; }
			GameObject* GetDiscByIndex(size_t discIndex) { return m_pDiscs[discIndex]; }

			void IncreaseTouchedCubes() { m_TouchedCubes++; }
			int GetNbrOfTouchedCubes() const { return m_TouchedCubes; }

			bool ColorCube(const size_t index);

		protected:
			virtual void Initialize(Scene* pParentScene) override;
			virtual void PostInitialize(Scene* pParentScene) override;
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
			std::vector<GameObject*> m_pCubes;
			//std::vector<Cube*> m_pCubes;
			std::vector<GameObject*> m_pDiscs;
			//std::vector<Disc*> m_pDiscs;

			void Create_AddConnections(std::vector<std::pair<int, std::vector<int>>>& connectionsToCubes,
									   std::vector<std::pair<int, std::vector<int>>>& connectionsToDiscs);
			void AddConnections_Cubes(size_t cubeToEdit, std::vector<int> connectionIDs);
			void AddConnections_Discs(size_t cubeToEdit, std::vector<int> connectionIDs);

			bool LevelDone(const LevelNmr& levelNmr) const;
	};
}