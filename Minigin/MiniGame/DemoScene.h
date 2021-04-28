#pragma once
#include <Scene.h>

namespace Helheim
{
	class DemoScene final : public Scene
	{
		public:
			DemoScene();
			virtual ~DemoScene();

			DemoScene(const DemoScene&) = delete;
			DemoScene(DemoScene&&) noexcept = delete;
			DemoScene& operator=(const DemoScene&) = delete;
			DemoScene& operator=(DemoScene&&) noexcept = delete;

			virtual void Initialize() override;
			virtual void Update(const float elapsedSec) override;
			virtual void FixedUpdate(const float timeEachUpdate) override;
			virtual void LateUpdate() override;
			virtual void Render() const override;

		protected:

		private:
			void CreateBackground(Helheim::Scene& scene) const;
			void CreateLogo(Helheim::Scene& scene) const;
			void CreateFPSCounter(Helheim::Scene& scene) const;
			void CreateTitle(Helheim::Scene& scene) const;
			void CreateQBERTs(Helheim::Scene& scene) const;
			void CreateLEVEL(Helheim::Scene& scene) const;
	};
}
