#pragma once
#include <Scene.h>
namespace Helheim
{
	class QBERT;
	class Level;
	class GameObject;
	class LevelComponent;
	class Scene_03 : public Scene
	{
		public:
			Scene_03(const int windowWidth, const int windowHeight, const bool isActive);
			virtual ~Scene_03() = default;

			Scene_03(const Scene_03&) = delete;
			Scene_03(Scene_03&&) noexcept = delete;
			Scene_03& operator=(const Scene_03&) = delete;
			Scene_03& operator=(Scene_03&&) noexcept = delete;

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