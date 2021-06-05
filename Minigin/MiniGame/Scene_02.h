#pragma once
#include <Scene.h>

namespace Helheim
{
	class QBERT;
	class Level;
	class GameObject;
	class LevelComponent;
	class Scene_02 : public Scene
	{
		public:
			Scene_02(const int windowWidth, const int windowHeight, const bool isActive);
			virtual ~Scene_02();

			Scene_02(const Scene_02&) = delete;
			Scene_02(Scene_02&&) noexcept = delete;
			Scene_02& operator=(const Scene_02&) = delete;
			Scene_02& operator=(Scene_02&&) noexcept = delete;

			virtual void Initialize() override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;
			virtual void LateUpdate() override;
			virtual void Render() const override;

			Level* GetLevel() const;

		protected:

		private:
			Level* m_pLevel;

			void InitializeLevel();
	};
}

