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

			void Initialize();
			void PostInitialize();
			void Update(const float elapsedSec);
			void FixedUpdate(const float timeEachUpdate);
			void Render();
			
			//Scene& CreateScene(const std::string& name);
			void AddGameScene(Scene* pScene);
			void AddMenuScene(Scene* pScene);
			void SetActiveGameSceneIndex(const int activeSceneIdx) { m_ActiveGameSceneIndex = activeSceneIdx; }
			void SetActiveMenuSceneIndex(const int activeSceneIdx) { m_ActiveGameSceneIndex = activeSceneIdx; }

			Scene* GetActiveGameScene() const { return m_pGameScenes[m_ActiveGameSceneIndex]; }
			int GetActiveGameSceneIndex() const { return m_ActiveGameSceneIndex; }
			Scene* GetActiveMenuScene() const { return m_pMenuScenes[m_ActiveMenuSceneIndex]; }
			int GetActiveMenuSceneIndex() const { return m_ActiveGameSceneIndex; }

			void DeactivateAllGameScenes();
			void DeactivateAllMenuScenes();

			void ActivateNextGameScene();
			
			void ActivateGameSceneByIndex(const size_t sceneIndex);
			void ActivateMenuSceneByIndex(const size_t sceneIndex);

		private:
			int m_ActiveGameSceneIndex;
			int m_ActiveMenuSceneIndex;
			std::vector<Scene*> m_pGameScenes;
			std::vector<Scene*> m_pMenuScenes;
	};
}
