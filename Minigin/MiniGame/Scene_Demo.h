#pragma once
#include <Scene.h>

namespace Helheim
{
	class Scene_Demo : public Helheim::Scene
	{
		public:
			Scene_Demo(const int windowWidth, const int windowHeight);
			virtual ~Scene_Demo() = default;

			Scene_Demo(const Scene_Demo&) = delete;
			Scene_Demo(Scene_Demo&&) noexcept = delete;
			Scene_Demo& operator=(const Scene_Demo&) = delete;
			Scene_Demo& operator=(Scene_Demo&&) noexcept = delete;

			virtual void Initialize() override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;
			virtual void LateUpdate() override;
			virtual void Render() const override;

		protected:

		private:
			void CreateBackground();
			void CreateLogo();
			void CreateFPSCounter();
			void CreateTitle();
			void CreateQBERTs();
			void CreateLEVEL();
	};
}