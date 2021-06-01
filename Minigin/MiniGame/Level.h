#pragma once

namespace Helheim
{
	class Scene;
	class GameObject;
	class LevelComponent;
	class Level final
	{
		public:
			Level();
			~Level() = default;

			Level(const Level&) = delete;
			Level(Level&&) noexcept = delete;
			Level& operator=(const Level&) = delete;
			Level& operator=(Level&&) noexcept = delete;

			void Initialize(Scene* pCurrentScene);

			GameObject* GetGameObject() const { return m_pLevelGO; }

		protected:

		private:
			GameObject* m_pLevelGO;
			LevelComponent* m_pLevelComponent;
	};
}