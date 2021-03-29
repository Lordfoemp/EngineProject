#pragma once
#include "Singleton.h"

namespace Helheim
{
	class Scene;
	class SceneManager final
	{
		public:
			SceneManager() = default;
			~SceneManager();
			Scene& CreateScene(const std::string& name);

			void Update(const float elapsedSec);
			void FixedUpdate(const float timeEachUpdate);
			void Render();

			Scene* GetActiveScene() const { return m_pScenes[m_ActiveSceneIndex]; }
		private:
			int m_ActiveSceneIndex;
			friend class Singleton<SceneManager>;
		
			std::vector<Scene*> m_pScenes;
	};
}
