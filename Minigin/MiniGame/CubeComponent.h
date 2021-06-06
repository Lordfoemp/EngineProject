#pragma once
#include <Component.h>

namespace Helheim
{
	class GameObject;
	class Connection;
	class TextureComponent;
	class CubeComponent : public Component
	{
		public:
			CubeComponent(Helheim::GameObject* pParentObject);
			virtual ~CubeComponent() = default;;

			CubeComponent(const CubeComponent&) = delete;
			CubeComponent(CubeComponent&&) noexcept = delete;
			CubeComponent& operator=(const CubeComponent&) = delete;
			CubeComponent& operator=(CubeComponent&&) noexcept = delete;

			bool ChangeColor();
			std::vector<Connection*> GetConnections() const { return m_pConnections; }
			int GetStepOnCounter() const { return m_StepCounter; }
			void AddConnections(Connection* pConnection) { m_pConnections.push_back(pConnection); }

			bool GetIsVisited() const { return m_IsVisited; }

		protected:
			virtual void Initialize(Scene * pParentScene) override;
			virtual void PostInitialize(Scene * pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			bool m_IsVisited;
			int m_StepCounter;
			TextureComponent* m_pTextureComponent;
			std::vector<Connection*> m_pConnections;
	};
}