#pragma once
#include <Component.h>
namespace Helheim
{
	class TextureComponent;
	class DiscComponent : public Component
	{
		public:
			DiscComponent(Helheim::GameObject* pParentObject);
			virtual ~DiscComponent() = default;;

			DiscComponent(const DiscComponent&) = delete;
			DiscComponent(DiscComponent&&) noexcept = delete;
			DiscComponent& operator=(const DiscComponent&) = delete;
			DiscComponent& operator=(DiscComponent&&) noexcept = delete;

			void Activate() { m_IsActive = true; }

		protected:
			virtual void Initialize(Scene * pParentScene) override;
			virtual void PostInitialize(Scene * pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			bool m_IsUsed, 
				 m_IsActive,
				 m_GoingRight;
			TextureComponent* m_pTextureComponent;

			void UpdatePosition(const float elapsedSec);
			void UpdateNotifier();
	};
}