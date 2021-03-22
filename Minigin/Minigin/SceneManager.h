#pragma once
//#include "Singleton.h"

namespace Helheim
{
	class Scene;
	class SceneManager final/* : public Singleton<SceneManager>*/
	{
		public:
			SceneManager() = default;
			~SceneManager() = default;
			Scene& CreateScene(const std::string& name);

			void Update();
			void FixedUpdate();
			void Render();

			std::shared_ptr<Scene> GetActiveScene() const { return m_Scenes[m_ActiveSceneIndex]; }

		private:
			int m_ActiveSceneIndex;
			//friend class Singleton<SceneManager>;
			std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
