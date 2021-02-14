#include "MiniginPCH.h"
#include "TransformComponent.h"

#include "glm/vec3.hpp"

Helheim::TransformComponent::TransformComponent(std::shared_ptr<dae::GameObject> pParentObject, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
							: Component(pParentObject, false)
							, m_Position(position)
							, m_Rotation(rotation)
							, m_Scale(scale)
{}

void Helheim::TransformComponent::Initialize()
{}
void Helheim::TransformComponent::Update()
{}