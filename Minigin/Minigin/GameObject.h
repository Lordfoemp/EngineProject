#pragma once
#include "Transform.h"
#include "SceneObject.h"

#include "Component.h"
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
		public:
			GameObject(const glm::vec3& position = { 0, 0, 0 }, const glm::vec3& rotation = { 0, 0, 0 }, const glm::vec3& scale = { 1, 1, 1 });
			virtual ~GameObject() = default;;
			GameObject(const GameObject& other) = delete;
			GameObject(GameObject&& other) = delete;
			GameObject& operator=(const GameObject& other) = delete;
			GameObject& operator=(GameObject&& other) = delete;

			void Update() override;
			void Render() const override;

			void AddComponent(std::shared_ptr<Helheim::Component>(pComponent)) { m_pComponents.push_back(pComponent); };
			template <class T>
			std::shared_ptr<T> GetComponent() const;
			template <class T>
			std::vector<std::shared_ptr<T>> GetComponents() const;
			template <class T>
			bool HasComponent() const;

			void SetName(const std::string& name) { m_Name = name; }
			std::string GetName() const { return m_Name; }

		private:
			std::string m_Name{};
			std::vector<std::shared_ptr<Helheim::Component>> m_pComponents{};
	};

	template<class T>
	inline std::shared_ptr<T> GameObject::GetComponent() const
	{
		for (std::shared_ptr<Helheim::Component> pComp : m_pComponents)
		{
			std::shared_ptr<T> pTComponent = std::dynamic_pointer_cast<T>(pComp);
			if (pTComponent)
				return pTComponent;
		}
		return nullptr;
	}
	template<class T>
	inline std::vector<std::shared_ptr<T>> GameObject::GetComponents() const
	{
		std::vector<std::shared_ptr<T>> pTComponents{};
		for (std::shared_ptr<Helheim::Component> pComp : m_pComponents)
		{
			std::shared_ptr<T> pTComponent = std::dynamic_pointer_cast<T>(pComp);
			if (pTComponent)
				pTComponents->push_back(pTComponent);
		}
		return pTComponents;
	}
	template<class T>
	inline bool GameObject::HasComponent() const
	{
		std::shared_ptr<T> pComponent{ GetComponent<T>() };
		if (pComponent)
			return true;
		else
			return false;
	}
}
