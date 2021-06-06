#pragma once
#include <Component.h>

namespace Helheim
{
	class JumpComponent;
	class TextureComponent;
	class QBERTComponent final : public Component
	{
		public:
			QBERTComponent(Helheim::GameObject* pParentObject);
			virtual ~QBERTComponent() = default;;

			QBERTComponent(const QBERTComponent&) = delete;
			QBERTComponent(QBERTComponent&&) noexcept = delete;
			QBERTComponent& operator=(const QBERTComponent&) = delete;
			QBERTComponent& operator=(QBERTComponent&&) noexcept = delete;

			void SetJumpingSprite(const bool jumpLeft, const bool jumpUp);
			void Reset(const glm::vec3& cubeStartPosition);

		protected:
			virtual void Initialize(Scene * pParentScene) override;
			virtual void PostInitialize(Scene * pParentScene) override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;

		private:
			enum class StartPositionsTexture
			{
				LEFT_DOWN = 0,
				LEFT_UP = 16,
				RIGHT_DOWN = 32,
				RIGHT_UP = 48,
			};
			TextureComponent* m_pTextureComponent;
			JumpComponent* m_pJumpComponent;
	};
}