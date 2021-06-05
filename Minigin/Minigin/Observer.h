#pragma once
#include <vector>

namespace Helheim
{
	class GameObject;
	class Component;
	class Observer
	{
		public:
			enum class OBSERVER_EVENTS : int
			{
				NO_EVENT = 0,
				LOAD_NEXT_LEVEL,
				GAME_DONE,
				DELETE_DISC,
				PLAYER_DIED_P1,
				PLAYER_DIED_P2,
				COLOR_CHANGE_P1,
				COLOR_CHANGE_P2,
				COILY_DEAD_DISC_P1,
				COILY_DEAD_DISC_P2,
				CATCH_SLICK_P1,
				CATCH_SLICK_P2,
				CATCH_SAM_P1,
				CATCH_SAM_P2
			};

			Observer(Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~Observer() = default;

			Observer(const Observer&) = delete;
			Observer(Observer&&) noexcept = delete;
			Observer& operator=(const Observer&) = delete;
			Observer& operator=(Observer&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject* pObject, const OBSERVER_EVENTS& event) = 0;
			void SetOwnerComponent(Component* pOwnerComponent) { m_pOwningComponent = pOwnerComponent; }

		protected:
			Helheim::GameObject* m_pMessageReceiverP1;
			Helheim::GameObject* m_pMessageReceiverP2;
			Helheim::Component* m_pOwningComponent;

		private:
	};
}