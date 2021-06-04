#pragma once
#include "../Minigin/Observer.h"

namespace Helheim
{
	class Cube;
	class CubeObserver : public Observer
	{
		public:
			CubeObserver(Cube* pOwnerObject, Helheim::GameObject* pMessageRecieverP1, Helheim::GameObject* pMessageRecieverP2);
			virtual ~CubeObserver() = default;

			CubeObserver(const CubeObserver&) = delete;
			CubeObserver(CubeObserver&&) noexcept = delete;
			CubeObserver& operator=(const CubeObserver&) = delete;
			CubeObserver& operator=(CubeObserver&&) noexcept = delete;

			virtual void OnNotify(Helheim::GameObject * pObject, const OBSERVER_EVENTS & event) override;

		protected:

		private:
			Cube* m_pOwnerCube;
	};
}

