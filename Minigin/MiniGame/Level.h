#pragma once
#include <string>
#include "LevelComponent.h"

namespace Helheim
{
	class Scene;
	class GameObject;
	class Level final
	{
		public:
			Level();
			~Level() = default;

			Level(const Level&) = delete;
			Level(Level&&) noexcept = delete;
			Level& operator=(const Level&) = delete;
			Level& operator=(Level&&) noexcept = delete;

			void Initialize(Scene* pCurrentScene, const std::string& folder, const LevelComponent::LevelNmr& levelNmr);

			GameObject* GetGameObject() const { return m_pLevelGO; }
			LevelComponent* GetLevelComponent() const { return m_pLevelComponent; }

		protected:

		private:
			GameObject* m_pLevelGO;
			LevelComponent* m_pLevelComponent;
	};
}