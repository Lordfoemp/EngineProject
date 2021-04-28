#pragma once
#include "SceneManager.h"

namespace Helheim
{
	class GameObject;
	class Scene
	{
			//friend Scene& SceneManager::CreateScene(const std::string& name);
		public:
			Scene(const std::string& name);
			virtual ~Scene();

			Scene(const Scene& other) = delete;
			Scene(Scene&& other) = delete;
			Scene& operator=(const Scene& other) = delete;
			Scene& operator=(Scene&& other) = delete;

			virtual void Initialize() = 0;
			virtual void Update(const float elapsedSec) = 0;
			virtual void FixedUpdate(const float timeEachUpdate) = 0;
			virtual void LateUpdate() = 0;
			virtual void Render() const = 0;

			void AddGameObject(GameObject* object);
			Helheim::GameObject* GetObjectByName(const std::string& name) const;

		private:
			std::string m_Name;
			std::vector<GameObject*> m_pObjects{};
	};
}
