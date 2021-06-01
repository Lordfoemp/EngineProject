#pragma once
#include <string>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace Helheim
{
	class Scene;
	class GameObject;
	class QBERT final
	{
		public:
			QBERT(const std::string& name);
			~QBERT() = default;

			QBERT(const QBERT&) = delete;
			QBERT(QBERT&&) noexcept = delete;
			QBERT& operator=(const QBERT&) = delete;
			QBERT& operator=(QBERT&&) noexcept = delete;

			void Initialize(Scene* pCurrentScene, const glm::vec3& position);

			std::string GetName() const { return m_Name; }
			GameObject* GetGameObject_QBERT_Char() const { return m_pQBERTGO; }
			GameObject* GetGameObject_QBERT_Score() const { return m_pScoreGO; }

			void Jump(GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp);

		protected:

		private:
			size_t m_CurrentCubeIndex;
			std::string m_Name;
			GameObject* m_pQBERTGO;
			GameObject* m_pHealthGO;
			GameObject* m_pScoreGO;

			void InitializeQBERT(Scene* pCurrentScene, const glm::vec3& position);
			void InitializeHealth(Scene* pCurrentScene);
			void InitializeScore(Scene* pCurrentScene);
			void InitializeInput(Scene* pCurrentScene);
	};
}

