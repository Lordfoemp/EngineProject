#pragma once
#include <Scene.h>

namespace Helheim
{
	class QBERT;
	class Level;
	class GameObject;
	class LevelComponent;
	class Scene_01 : public Scene
	{
		public:
			Scene_01(const int windowWidth, const int windowHeight, const bool isActive);
			virtual ~Scene_01() = default;

			Scene_01(const Scene_01&) = delete;
			Scene_01(Scene_01&&) noexcept = delete;
			Scene_01& operator=(const Scene_01&) = delete;
			Scene_01& operator=(Scene_01&&) noexcept = delete;

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