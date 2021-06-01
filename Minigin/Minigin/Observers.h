#pragma once
#include "Observer.h"

namespace Helheim
{
	class GameObject;
}
namespace Helheim
{
	class TextComponent;
	class HealthComponent;
	class HealthObserver final : public Observer
	{
		public: 
			HealthObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~HealthObserver() = default;

			HealthObserver(const HealthObserver&) = delete;
			HealthObserver(HealthObserver&&) noexcept = delete;
			HealthObserver& operator=(const HealthObserver&) = delete;
			HealthObserver& operator=(HealthObserver&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS & event) override;

		protected:

		private:
			Helheim::GameObject* m_pMessageReceiver;
	};
	class ScoreObserver final : public Observer
	{
		public:
			ScoreObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~ScoreObserver() = default;

			ScoreObserver(const ScoreObserver&) = delete;
			ScoreObserver(ScoreObserver&&) noexcept = delete;
			ScoreObserver& operator=(const ScoreObserver&) = delete;
			ScoreObserver& operator=(ScoreObserver&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event) override;

		protected:

		private:
			int m_Score;
	};
	class LevelObserver final : public Observer
	{
		public:
			LevelObserver(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~LevelObserver() = default;

			LevelObserver(const LevelObserver&) = delete;
			LevelObserver(LevelObserver&&) noexcept = delete;
			LevelObserver& operator=(const LevelObserver&) = delete;
			LevelObserver& operator=(LevelObserver&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event) override;

		protected:

		private:
			int m_Score;
	};
}