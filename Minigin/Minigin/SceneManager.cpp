#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

//#include "Audio.h"

Helheim::SceneManager::SceneManager()
	: m_pGameScenes(std::vector<Scene*>())
	, m_ActiveGameSceneIndex()
{}
Helheim::SceneManager::~SceneManager()
{
	for (Helheim::Scene* pScene : m_pGameScenes)
		DELETE_POINTER(pScene);
}

void Helheim::SceneManager::Initialize()
{
	for (Helheim::Scene* scene : m_pMenuScenes)
		scene->Initialize();

	for (Helheim::Scene* scene : m_pGameScenes)
		scene->Initialize();
}
void Helheim::SceneManager::PostInitialize()
{
	for (Helheim::Scene* scene : m_pMenuScenes)
		scene->PostInitialize();

	for (Helheim::Scene* scene : m_pGameScenes)
		scene->PostInitialize();
}
void Helheim::SceneManager::Update(const float elapsedSec)
{
	for (Helheim::Scene* scene : m_pMenuScenes)
		scene->Update(elapsedSec);

	for (Helheim::Scene* scene : m_pGameScenes)
		scene->Update(elapsedSec);
}
void Helheim::SceneManager::FixedUpdate(const float timeEachUpdate)
{
	for (Helheim::Scene* scene : m_pMenuScenes)
		scene->FixedUpdate(timeEachUpdate);

	for (Helheim::Scene* scene : m_pGameScenes)
		scene->FixedUpdate(timeEachUpdate);
}
void Helheim::SceneManager::Render()
{
	for (Helheim::Scene* scene : m_pMenuScenes)
		scene->Render();

	for (Helheim::Scene* const scene : m_pGameScenes)
		scene->Render();
}

//Helheim::Scene& Helheim::SceneManager::CreateScene(const std::string& name)
//{
//	Scene* const scene = new Scene(name);
//	m_pScenes.push_back(scene);
//	m_ActiveSceneIndex = (int)(m_pScenes.size() - 1);
//	return *scene;
//}
void Helheim::SceneManager::AddGameScene(Scene* pScene)
{
	m_pGameScenes.push_back(pScene);
	m_ActiveGameSceneIndex = 0;
}
void Helheim::SceneManager::AddMenuScene(Scene* pScene)
{
	m_pMenuScenes.push_back(pScene);
	m_ActiveMenuSceneIndex = 0;
}

void Helheim::SceneManager::DeactivateAllGameScenes()
{
	for (Scene* pScene : m_pGameScenes)
		pScene->DeactivateScene();
}
void Helheim::SceneManager::DeactivateAllMenuScenes()
{
	for (Scene* pScene : m_pMenuScenes)
		pScene->DeactivateScene();
}

void Helheim::SceneManager::ActivateNextGameScene()
{
	// Deactivate current scene
	m_pGameScenes[size_t(m_ActiveGameSceneIndex)]->DeactivateScene();

	// Increment index that remembers which scene the game is on
	m_ActiveGameSceneIndex++;

	// Activate the new current scene
	m_pGameScenes[size_t(m_ActiveGameSceneIndex)]->ActivateScene();
}

void Helheim::SceneManager::ActivateGameSceneByIndex(const size_t sceneIndex)
{
	m_pGameScenes[sceneIndex]->ActivateScene();
	m_ActiveGameSceneIndex = int(sceneIndex);
}
void Helheim::SceneManager::ActivateMenuSceneByIndex(const size_t sceneIndex)
{
	m_pMenuScenes[sceneIndex]->ActivateScene();
	m_ActiveMenuSceneIndex = int(sceneIndex);
}
