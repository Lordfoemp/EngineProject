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
	if (m_JumpingLeftUp || m_JumpingLeftDown)
	{
		x -= (10 * elapsedSec);
	}
	else if (m_JumpingRightUp || m_JumpingRightDown)
	{
		x += (10 * elapsedSec);
	}

	// Vertical velocity
	float fallVelocity{};
	if (m_JumpingLeftUp || m_JumpingRightUp)
	{
		fallVelocity = { ((m_FallSpeed += m_FallSpeedModifier) * elapsedSec) * 3 };
	}
	else
		fallVelocity = { ((m_FallSpeed += m_FallSpeedModifier) * elapsedSec) };
	float y{ currentPosition.y + fallVelocity };
	std::cout << "currentPosition: " << y << '\n';

	// Depth	
	float z{ currentPosition.z };

	//m_OldYPosition = currentPosition.y;
	pTransformComponent->SetPosition({ x, y, z});
	//if (m_OldYPosition <= y)
	//	m_pParentObject->GetComponent<ColliderComponent>()->SetCollisionState(ColliderComponent::CollisionState::FALLING);
	//else
	//	m_pParentObject->GetComponent<ColliderComponent>()->SetCollisionState(ColliderComponent::CollisionState::JUMPING);
}
void Helheim::PhysicsComponent::FixedUpdate(const float ) // timeEachUpdate
{
}