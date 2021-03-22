#pragma once

namespace Helheim
{
	class Scene;
}
struct SDL_Window;
namespace Helheim
{
	class Locator;
	class Minigin
	{
		public:
			void Initialize();
			void LoadGame() const;
			void Cleanup();
			void Run();
		private:
			SDL_Window* m_pWindow{};
			Locator* m_pLocator{};

			void InitializeConsole();
			void InitializeLocator();

			void CreateBackground(Helheim::Scene& scene) const;
			void CreateLogo(Helheim::Scene& scene) const;
			void CreateFPSCounter(Helheim::Scene& scene) const;
			void CreateTitle(Helheim::Scene& scene) const;
			void CreateQBERTs(Helheim::Scene& scene) const;
			void CreateLEVEL(Helheim::Scene& scene) const;
	};
}