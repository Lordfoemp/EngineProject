#pragma once
#include "Component.h"

namespace Helheim
{
	class PhysicsComponent : public Component
	{
		public:
			PhysicsComponent(Helheim::GameObject* pParentObject);
			virtual ~PhysicsComponent() = default;;

			PhysicsComponent(const PhysicsComponent&) = delete;
			PhysicsComponent(PhysicsComponent&&) noexcept = delete;
			PhysicsComponent& operator=(const PhysicsComponent&) = delete;
			PhysicsComponent& operator=(PhysicsComponent&&) noexcept = delete;

			void SetJumpForce(const float force, const bool jumpingLeft, const bool jumpingUp);

			void SetJumping() { m_FallSpeed = -m_FallSpeed; };
			void ResetFallSpeed() { m_FallSpeed = 75.f; }

			void Activate() { m_Active = true; }
			void Deactivate() { m_Active = false; }

		protected:
			virtual void Initialize(Scene * pParentScene) override;
			virtual void PostInitialize(Scene* pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			float m_OldYPosition;

			bool m_Active;
			
			bool m_JumpingLeftUp;
			bool m_JumpingRightUp;
			bool m_JumpingLeftDown;
			bool m_JumpingRightDown;

			float m_JumpForce_Horizontal;
			float m_JumpForce_Vertical;
			float m_FallSpeed;
			float m_FallSpeedModifier;
			float m_Gravity;
	};
}