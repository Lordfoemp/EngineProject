#pragma once
#include "Component.h"

// GLM Includes
#include "glm/vec3.hpp"

namespace Helheim
{
	class TransformComponent final : public Component
	{
		public:
			TransformComponent(std::shared_ptr<dae::GameObject> pParentObject, const glm::vec3& position = { 0, 0, 0 }, const glm::vec3& rotation = { 0, 0, 0 }, const glm::vec3& scale = { 0, 0, 0 });
			virtual ~TransformComponent() = default;

			TransformComponent(const TransformComponent&) = delete;
			TransformComponent(TransformComponent&&) noexcept = delete;
			TransformComponent& operator=(const TransformComponent&) = delete;
			TransformComponent& operator=(TransformComponent&&) noexcept = delete;

			void SetPosition(const glm::vec3& position) { m_Position = position; }
			void SetPosition(const float x, const float y, const float z) 
			{ 
				m_Position.x = x;
				m_Position.y = y;
				m_Position.z = z;
			}
			void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
			void SetRotation(const float x, const float y, const float z)
			{
				m_Rotation.x = x;
				m_Rotation.y = y;
				m_Rotation.z = z;
			}
			void SetScale(const glm::vec3& scale) { m_Scale = scale; }
			void SetScale(const float x, const float y, const float z)
			{
				m_Scale.x = x;
				m_Scale.y = y;
				m_Scale.z = z;
			}

			glm::vec3 GetPosition() const { return m_Position; };
			glm::vec3 GetRotation() const { return m_Rotation; };
			glm::vec3 GetScale() const { return m_Scale; };

		protected:
			virtual void Initialize() override;
			virtual void Update() override;

		private:
			glm::vec3 m_Position;
			glm::vec3 m_Rotation;
			glm::vec3 m_Scale;
	};
}