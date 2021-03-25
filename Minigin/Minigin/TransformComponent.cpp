#include "MiniginPCH.h"
#include "TransformComponent.h"

Helheim::TransformComponent::TransformComponent(Helheim::GameObject* pParentObject, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
							: Component(pParentObject, false)
							, m_Position(position)
							, m_Rotation(rotation)
							, m_Scale(scale)
{}

void Helheim::TransformComponent::Initialize()
{}
void Helheim::TransformComponent::Update()
{}
void Helheim::TransformComponent::FixedUpdate()
{}