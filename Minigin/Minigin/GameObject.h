#pragma once
#include "Transform.h"
#include "SceneObject.h"
 
// Helheim Includes
#include "Component.h"

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
		public:
			GameObject();
			virtual ~GameObject() = default;

			GameObject(const GameObject& other) = delete;
			GameObject(GameObject&& other) = delete;
			GameObject& operator=(const GameObject& other) = delete;
			GameObject& operator=(GameObject&& other) = delete;

			void Update() override;
			void Render() const override;

			void SetTexture(const std::string& filename);
			void SetPosition(float x, float y);

			void AddComponent(Helheim::Component* component) 
			{ m_Components.push_back(component); }


		private:
			Transform m_Transform;
			std::shared_ptr<Texture2D> m_Texture{};

			//new
			std::vector<Helheim::Component*> m_Components;
	};
}
