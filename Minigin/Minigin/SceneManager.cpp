#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

//#include "Audio.h"

Helheim::SceneManager::SceneManager()
	: m_pScenes(std::vector<Scene*>())
	, m_ActiveSceneIndex()
{}
Helheim::SceneManager::~SceneManager()
{
	for (Helheim::Scene* pScene : m_pScenes)
		DELETE_POINTER(pScene);
}

void Helheim::SceneManager::Update(const float elapsedSec)
{
	for (Helheim::Scene* scene : m_pScenes)
		scene->Update(elapsedSec);
}
void Helheim::SceneManager::FixedUpdate(const float timeEachUpdate)
{
	for (Helheim::Scene* scene : m_pScenes)
		scene->FixedUpdate(timeEachUpdate);
}
void Helheim::SceneManager::Render()
{
	for (Helheim::Scene* const scene : m_pScenes)
		scene->Render();
}

//Helheim::Scene& Helheim::SceneManager::CreateScene(const std::string& name)
//{
//	Scene* const scene = new Scene(name);
//	m_pScenes.push_back(scene);
//	m_ActiveSceneIndex = (int)(m_pScenes.size() - 1);
//	return *scene;
//}
void Helheim::SceneManager::AddScene(Scene* pScene)
{
	m_pScenes.push_back(pScene);
	m_ActiveSceneIndex = 0;
}

void Helheim::SceneManager::ActivateNextScene()
{
	// Deactivate current scene
	m_pScenes[size_t(m_ActiveSceneIndex)]->DeactivateScene();

	// Increment index that remembers which scene the game is on
	m_ActiveSceneIndex++;

	// Activate the new current scene
	m_pScenes[size_t(m_ActiveSceneIndex)]->ActivateScene();
}