#pragma once
#include "Component.h"

namespace Helheim
{
	class Font;
	class GameObject;
}
namespace Helheim
{
	class TextComponent;
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
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void FixedUpdate() override;

		private:
			int m_Score;
	};
}
