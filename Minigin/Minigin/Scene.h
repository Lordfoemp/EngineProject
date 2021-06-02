#pragma once
//#include "SceneManager.h"
#include <vector>
#include <string>

namespace Helheim
{
	class QBERT;
	class GameObject;
	class Scene
	{
		public:
			Scene(const int windowWidth, const int windowHeight, const bool isActive);
			virtual ~Scene();

			Scene(const Scene& other) = delete;
			Scene(Scene&& other) = delete;
			Scene& operator=(const Scene& other) = delete;
			Scene& operator=(Scene&& other) = delete;

			virtual void Initialize() = 0;
			virtual void Update(const float elapsedSec) = 0;
			virtual void FixedUpdate(const float timeEachUpdate) = 0;
			virtual void LateUpdate() = 0;
			virtual void Render() const = 0;

			void AddGameObject(GameObject* object);
			Helheim::GameObject* GetObjectByName(const std::string& name) const;

			int GetWindowWidth() const { return m_WindowWidth; }
			int GetWindowHeight() const { return m_WindowHeight; }

			void ActivateScene() { m_IsActive = true; }
			void DeactivateScene() { m_IsActive = false; }

			void SetQbert(QBERT* pQBERT) { m_pQBERT = pQBERT; }
			QBERT* GetQBERT() const { return m_pQBERT; }

		private:
			bool m_IsActive;
			int m_WindowWidth;
			int m_WindowHeight;
			std::string m_Name;
			QBERT* m_pQBERT;
			std::vector<GameObject*> m_pObjects{};
	};
}
