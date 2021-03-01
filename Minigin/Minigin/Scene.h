#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include "SceneObject.h"

namespace dae
{
	
	class Scene
	{
			friend Scene& SceneManager::CreateScene(const std::string& name);
		public:
			void Add(const std::shared_ptr<SceneObject>& object);

			void Update();
			void Render() const;

			~Scene();
			Scene(const Scene& other) = delete;
			Scene(Scene&& other) = delete;
			Scene& operator=(const Scene& other) = delete;
			Scene& operator=(Scene&& other) = delete;

			std::shared_ptr<dae::GameObject> GetObjectByName(const std::string& name) const;

		private:
			explicit Scene(const std::string& name);

			std::string m_Name;
			std::vector <std::shared_ptr<SceneObject>> m_Objects{};

			static unsigned int m_IdCounter;
	};

	inline std::shared_ptr<dae::GameObject> Scene::GetObjectByName(const std::string& name) const
	{
		for (auto pSceneObject : m_Objects)
		{
			std::shared_ptr<dae::GameObject> pGameObject = std::dynamic_pointer_cast<dae::GameObject>(pSceneObject);
			if (pGameObject)
				if (pGameObject->GetName() == name)
					return pGameObject;
		}
		return nullptr;
	}
}
