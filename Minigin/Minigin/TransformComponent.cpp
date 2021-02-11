#include "MiniginPCH.h"
#include "TransformComponent.h"

#include "glm/vec3.hpp"

Helheim::TransformComponent::TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
							: m_Position(position)
							, m_Rotation(rotation)
							, m_Scale(scale)
{}

void Helheim::TransformComponent::Initialize()
{}
void Helheim::TransformComponent::Update()
{}
void Helheim::TransformComponent::Draw()
{}