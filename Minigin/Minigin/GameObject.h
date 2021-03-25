#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace Helheim
{
	class Component;
	class GameObject final
	{
		public:
			GameObject(const glm::vec3& position = { 0, 0, 0 }, const glm::vec3& rotation = { 0, 0, 0 }, const glm::vec3& scale = { 1, 1, 1 });
			~GameObject();
			GameObject(const GameObject& other) = delete;
			GameObject(GameObject&& other) = delete;
			GameObject& operator=(const GameObject& other) = delete;
			GameObject& operator=(GameObject&& other) = delete;

			void Update();
			void FixedUpdate();
			void Render() const;

			void AddComponent(Helheim::Component* pComponent) { m_pComponents.push_back(pComponent); };
			template <class T>
			T* GetComponent() const;
			template <class T>
			std::vector<T*> GetComponents() const;
			template <class T>
			bool HasComponent() const;

			void SetName(const std::string& name) { m_Name = name; }
			std::string GetName() const { return m_Name; }

		private:
			std::string m_Name{};
			std::vector<Helheim::Component*> m_pComponents{};
	};

	template<class T>
	inline T* GameObject::GetComponent() const
	{
		for (Helheim::Component* pComp : m_pComponents)
		{
			T* pTComponent = dynamic_cast<T*>(pComp);
			if (pTComponent)
				return pTComponent;
		}
		return nullptr;
	}
	template<class T>
	inline std::vector<T*> GameObject::GetComponents() const
	{
		std::vector<T*> pTComponents{};
		for (Helheim::Component* pComp : m_pComponents)
		{
			T* pTComponent = dynamic_cast<T*>(pComp);
			if (pTComponent)
				pTComponents->push_back(pTComponent);
		}
		return pTComponents;
	}
	template<class T>
	inline bool GameObject::HasComponent() const
	{
		T* pComponent{ GetComponent<T>() };
		if (pComponent)
			return true;
		else
			return false;
	}
}
