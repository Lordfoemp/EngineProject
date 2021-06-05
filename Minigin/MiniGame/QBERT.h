#pragma once
#include <string>

namespace Helheim
{
	class Scene;
	class GameObject;
	class TextureComponent;
	class QBERT final
	{
		public:
			QBERT(const std::string& name);
			~QBERT();

			QBERT(const QBERT&) = delete;
			QBERT(QBERT&&) noexcept = delete;
			QBERT& operator=(const QBERT&) = delete;
			QBERT& operator=(QBERT&&) noexcept = delete;

			void Initialize(const glm::vec3& position);

			void AddToScene(Scene* pCurrentScene, const int sceneIdx);

			std::string GetName() const { return m_Name; }
			GameObject* GetGameObject_QBERT_Char() const { return m_pQBERTGO; }
			GameObject* GetGameObject_QBERT_Score() const { return m_pScoreGO; }

			bool Jump(const bool jumpLeft, const bool jumpUp);
			void Score();
			void Escape(const bool jumpLeft, const bool jumpUp);
			
			void SetJumpingSprite(const bool jumpLeft, const bool jumpUp);
			size_t GetCurrentCubeIndex() const { return m_CurrentCubeIndex; }
			void ResetAllSprites();

			void Reset(const glm::vec3& cubeStartPosition);

		protected:

		private:
			glm::vec3 m_StartPosition;
			size_t m_CurrentCubeIndex;
			std::string m_Name;
			
			TextureComponent* m_pTextureComponent_Qbert_LeftDown;
			TextureComponent* m_pTextureComponent_Qbert_LeftUp;
			TextureComponent* m_pTextureComponent_Qbert_RightDown;
			TextureComponent* m_pTextureComponent_Qbert_RightUp;
			GameObject* m_pQBERTGO;
			GameObject* m_pHealthGO;
			GameObject* m_pScoreGO;

			void InitializeQBERT(const glm::vec3& position);
			void InitializeHealth();
			void InitializeScore();
			void InitializeInput();
	};
}

