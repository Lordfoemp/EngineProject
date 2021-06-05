#pragma once
#include "Component.h"

namespace Helheim
{
	class Scene;
	class GameObject;
	class ColliderComponent : public Component
	{
		public:
			enum class CollisionState
			{
				ON_GROUND,
				FALLING,
				JUMPING,
				ESCAPE
			};
			enum class CharacterState
			{
				JUMPING,
				ESCAPE
			};
			ColliderComponent(Helheim::GameObject* pParentObject);
			virtual ~ColliderComponent() = default;

			ColliderComponent(const ColliderComponent & other) = delete;
			ColliderComponent(ColliderComponent && other) noexcept = delete;
			ColliderComponent& operator=(const ColliderComponent & other) = delete;
			ColliderComponent& operator=(ColliderComponent && other) noexcept = delete;

			void SetLevelObject(GameObject* pLevelGO) { m_pLevelGO = pLevelGO; }
			
			void SetCollisionInformation(const bool jumpLeft, const bool jumpUp)
			{
				m_JumpingLeft = jumpLeft;
				m_JumpingUp = jumpUp;
			}

			void SetCollisionState(const CollisionState& collisionState) { m_CollisionState = collisionState; }
			void SetCharacterState(const CharacterState& characterState) { m_CharacterState = characterState; }
			CollisionState GetCollisionState() const { return m_CollisionState; }
			CharacterState GetCharacterState() const { return m_CharacterState; }

			void SetTargetCubeIndex(const size_t currentCubeIndex) { m_TargetCubeIndex = currentCubeIndex; }
			void SetTargetDiscIndex(const size_t currentDiscIndex) { m_TargetDiscIndex = currentDiscIndex; }

			void Reset();

		protected:
			virtual void Initialize(Scene* pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;
		
		private:
			float oldpos{FLT_MAX};
			bool m_JumpingLeft;
			bool m_JumpingUp;

			glm::vec3 m_Rect;
			glm::vec3 m_Pos;
			glm::vec3 m_Color;
			size_t m_TargetCubeIndex;
			size_t m_TargetDiscIndex;
			CollisionState m_CollisionState;
			CharacterState m_CharacterState;
			GameObject* m_pLevelGO;
	};
}