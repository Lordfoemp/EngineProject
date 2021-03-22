#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Helheim::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
		scene->Update();
}
void Helheim::SceneManager::FixedUpdate()
{
	for (auto& scene : m_Scenes)
		scene->FixedUpdate();
}
void Helheim::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
		scene->Render();
}

Helheim::Scene& Helheim::SceneManager::CreateScene(const std::string& name)
{
	const std::shared_ptr<Scene> scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_ActiveSceneIndex = (int)(m_Scenes.size() - 1);

	return *scene;
}
