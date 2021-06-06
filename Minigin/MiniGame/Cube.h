#pragma once
#include <vector>
#include <string>

namespace Helheim
{
	class Scene;
	class Observer;
	class Connection;
	class GameObject;
	class TextureComponent;
	class Cube final
	{
		public:
			Cube();
			~Cube();

			Cube(const Cube&) = delete;
			Cube(Cube&&) noexcept = delete;
			Cube& operator=(const Cube&) = delete;
			Cube& operator=(Cube&&) noexcept = delete;

			void Initialize(Scene* pCurrentScene, const glm::vec3& pos, const std::string& folderpath);
			//void Update();

			void AddConnections(Connection* pConnection) { m_pConnections.push_back(pConnection); }
			std::vector<Connection*> GetConnections() const { return m_pConnections; }
			GameObject* GetGameObject() const { return m_pCubeGO; }

			bool GetIsColored() const { return m_IsColored; }

			void IncrementStepOnCounter() { m_StepOnCounter++; }
			int GetStepOnCounter() const { return m_StepOnCounter; }

		protected:

		private:
			enum class StartPositionsTexture
			{
				BASE = 0,
				COLOR_01 = 32,
				COLOR_02 = 64
			};
			bool m_IsColored;
			bool m_IsComplete;
			int m_StepOnCounter;
			GameObject* m_pCubeGO;
			std::vector<Connection*> m_pConnections;
	};
}
