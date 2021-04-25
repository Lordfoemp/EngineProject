#pragma once
#include "SceneManager.h"

namespace Helheim
{
	class GameObject;
	class Scene
	{
			friend Scene& SceneManager::CreateScene(const std::string& name);
		public:
			void Add(GameObject* object);

			void Update(const float elapsedSec);
			void FixedUpdate(const float timeEachUpdate);
			void LateUpdate() {};
			void Render() const;

			~Scene();
			Scene(const Scene& other) = delete;
			Scene(Scene&& other) = delete;
			Scene& operator=(const Scene& other) = delete;
			Scene& operator=(Scene&& other) = delete;

			Helheim::GameObject* GetObjectByName(const std::string& name) const;

		private: 
			explicit Scene(const std::string& name);

			std::string m_Name;
			std::vector<GameObject*> m_pObjects{};

			static unsigned int m_IdCounter; 
	};
}
