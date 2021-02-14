#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
		public:
			SceneManager() = default;
			~SceneManager() = default;
			Scene& CreateScene(const std::string& name);

			void Update();
			void Render();
		private:
			friend class Singleton<SceneManager>;
			std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
