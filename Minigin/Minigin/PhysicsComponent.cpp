#include "MiniginPCH.h"
#include "PhysicsComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

#include "ColliderComponent.h"

Helheim::PhysicsComponent::PhysicsComponent(Helheim::GameObject* pParentObject)
						  : Component(pParentObject, false)
						  , m_FallSpeed(75.f)
						  , m_FallSpeedModifier(1.5f)
						  , m_Gravity(9.81f)
{}

void Helheim::PhysicsComponent::SetJumpForce(const float force, const bool jumpingLeft, const bool jumpingUp)
{
	m_JumpingLeftUp = false;
	m_JumpingLeftDown = false;
	m_JumpingRightUp = false;
	m_JumpingRightDown = false;

	if (jumpingLeft)
	{
		if (jumpingUp)
			m_JumpingLeftUp = true;
		else
			m_JumpingLeftDown = true;

		m_JumpForce_Horizontal = force;
	}
	else
	{
		if (jumpingUp)
			m_JumpingRightUp = true;
		else
			m_JumpingRightDown = true;

		m_JumpForce_Horizontal = force;
	}
}

void Helheim::PhysicsComponent::Initialize(Scene* )	//pParentScene
{
}
void Helheim::PhysicsComponent::Update(const float elapsedSec)
{
	GameObject* pPlayerObject{ m_pParentObject };
	if (pPlayerObject->GetComponent<ColliderComponent>()->GetCollisionState() == ColliderComponent::CollisionState::ON_GROUND)
		return;

	TransformComponent* pTransformComponent{ pPlayerObject->GetComponent<TransformComponent>() };

	auto currentPosition{ pTransformComponent->GetPosition() };

	// Horizontal velocity
	float x{ currentPosition.x };
	const float horizontalSpeedMod{ (pPlayerObject->GetComponent<ColliderComponent>()->GetCharacterState() == ColliderComponent::CharacterState::JUMPING) ? 10.f : 22.5f };
	if (m_JumpingLeftUp || m_JumpingLeftDown)
	{
		x -= (horizontalSpeedMod * elapsedSec);
	}
	else if (m_JumpingRightUp || m_JumpingRightDown)
	{
		x += (horizontalSpeedMod * elapsedSec);
	}

	// Vertical velocity
	float fallVelocity{};
	float y{};
	if (m_JumpingLeftUp || m_JumpingRightUp)
	{
		fallVelocity = { ((m_FallSpeed += m_FallSpeedModifier) * elapsedSec) * 2 };
		y = { currentPosition.y + fallVelocity };
	}
	else
	{
		fallVelocity = { ((m_FallSpeed += m_FallSpeedModifier) * elapsedSec) };
		y = { currentPosition.y + fallVelocity };
	}
	
	if (pPlayerObject->GetComponent<ColliderComponent>()->GetCollisionState() == ColliderComponent::CollisionState::FALLING)
		y = { currentPosition.y + fallVelocity };

	// Depth	
	float z{ currentPosition.z };

	pTransformComponent->SetPosition({ x, y, z});
}
void Helheim::PhysicsComponent::FixedUpdate(const float ) // timeEachUpdate
{
}