#pragma once
#include <Component.h>

namespace Helheim
{
	class Cube;
	class Disc;
	class Connection;
	class LevelComponent;
    class JumpComponent final : public Component
    {
		public:
			JumpComponent(Helheim::GameObject* pParentObject);
			virtual ~JumpComponent() = default;;

			JumpComponent(const JumpComponent&) = delete;
			JumpComponent(JumpComponent&&) noexcept = delete;
			JumpComponent& operator=(const JumpComponent&) = delete;
			JumpComponent& operator=(JumpComponent&&) noexcept = delete;

			bool Jump(const bool jumpLeft, const bool jumpUp);
			void Escape(const bool jumpLeft, const bool jumpUp);
			
			void ResetCurrentCubeIndex() { m_CurrentCubeIndex = 0; }
			size_t GetCurrentCubeIndex() { return m_CurrentCubeIndex; }
			void ResetCurrentDiscIndex() { m_CurrentDiscIndex = 0; }
			size_t GetCurrentDiscIndex() { return m_CurrentDiscIndex; }

		protected:
			virtual void Initialize(Scene * pParentScene) override;
			virtual void PostInitialize(Scene * pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			size_t m_CurrentCubeIndex,
				   m_CurrentDiscIndex;

			LevelComponent* FindLevelComponent();
			GameObject* FindConnectingCube(std::vector<Connection*>& pConnections, const glm::vec3& currentPositionQBERT, const bool jumpLeft, const bool jumpUp);
			GameObject* FindConnectingDisc(std::vector<Connection*>& pConnections, const glm::vec3& currentPositionQBERT, const bool jumpLeft, const bool jumpUp);
    };
}

