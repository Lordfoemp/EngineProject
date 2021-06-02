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
			~Cube() = default;

			Cube(const Cube&) = delete;
			Cube(Cube&&) noexcept = delete;
			Cube& operator=(const Cube&) = delete;
			Cube& operator=(Cube&&) noexcept = delete;

			void Initialize(Scene* pCurrentScene, const glm::vec3& pos, const std::string& folderpath, Observer* pObserver);
			void Update();

			void AddConnections(Connection* pCube) { m_pConnections.push_back(pCube); }
			std::vector<Connection*> GetConnections() const { return m_pConnections; }
			GameObject* GetGameObject() const { return m_pCubeGO; }

			void ChangeColor();
			bool GetIsColored() const { return m_IsColored; }

			void IncrementStepOnCounter() { m_StepOnCounter++; }
			int GetStepOnCounter() const { return m_StepOnCounter; }

		protected:

		private:
			bool m_IsColored;
			bool m_IsComplete;
			int m_StepOnCounter;
			Observer* m_pObserver;
			GameObject* m_pCubeGO;
			TextureComponent* m_pTexture_Base;
			TextureComponent* m_pTexture_Colored_01;
			TextureComponent* m_pTexture_Colored_02;
			std::vector<Connection*> m_pConnections;

			void ChangeTextures(const bool texture01, const bool texture02, const bool texture03);
	};
}
