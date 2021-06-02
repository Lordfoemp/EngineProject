#pragma once
#include "Component.h"

namespace Helheim
{
	class ScoreComponent : public Component
	{
		public:
			ScoreComponent(Helheim::GameObject* pParentObject);
			virtual ~ScoreComponent() = default;;

			ScoreComponent(const ScoreComponent&) = delete;
			ScoreComponent(ScoreComponent&&) noexcept = delete;
			ScoreComponent& operator=(const ScoreComponent&) = delete;
			ScoreComponent& operator=(ScoreComponent&&) noexcept = delete;

			void IncreaseScore(const int score) { m_Score += score; }
			void DecreaseScore(const int score) { m_Score -= score; }
			int GetScore() const { return m_Score; }

		protected:
			virtual void Initialize(Scene* pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			int m_Score;
			int m_OldScore;
	};
}
