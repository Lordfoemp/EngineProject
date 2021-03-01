#pragma once

namespace dae
{
	class Scene;
}
struct SDL_Window;
namespace Helheim
{
	class Minigin
	{
		public:
			void Initialize();
			void LoadGame() const;
			void Cleanup();
			void Run();
		private:
			SDL_Window* m_pWindow{};

			void InitializeConsole();

			void CreateBackground(dae::Scene& scene) const;
			void CreateLogo(dae::Scene& scene) const;
			void CreateFPSCounter(dae::Scene& scene) const;
			void CreateTitle(dae::Scene& scene) const;
			void CreateQBERTs(dae::Scene& scene) const;
			void CreateLEVEL(dae::Scene& scene) const;
	};
}