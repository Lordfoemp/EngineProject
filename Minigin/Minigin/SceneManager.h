#pragma once
#include <string>
#include <vector>

namespace Helheim
{
	class Scene;
	class SceneManager final
	{
		public:
			SceneManager();
			~SceneManager();

			void Update(const float elapsedSec);
			void FixedUpdate(const float timeEachUpdate);
			void Render();
			
			//Scene& CreateScene(const std::string& name);
			void AddScene(Scene* pScene);
			void SetActiveSceneIndex(const int activeSceneIdx) { m_ActiveSceneIndex = activeSceneIdx; }

			Scene* GetActiveScene() const { return m_pScenes[m_ActiveSceneIndex]; }
			int GetActiveSceneIndex() const { return m_ActiveSceneIndex; }
		private:
			int m_ActiveSceneIndex;
			std::vector<Scene*> m_pScenes;
	};
}
