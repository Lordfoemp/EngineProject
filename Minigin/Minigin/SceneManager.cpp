#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Audio.h"

void Helheim::SceneManager::Update()
{
	//#if _DEBUG
	//Helheim::Locator::GetAudioService<LoggingAudio>()->Update();
	//#else
	//Helheim::Locator::GetAudioService<ConsoleAudio>()->Update();
	//#endif

	for (Helheim::Scene* scene : m_pScenes)
		scene->Update();
}
void Helheim::SceneManager::FixedUpdate()
{
	for (Helheim::Scene* scene : m_pScenes)
		scene->FixedUpdate();
}
void Helheim::SceneManager::Render()
{
	for (Helheim::Scene* const scene : m_pScenes)
		scene->Render();
}

Helheim::SceneManager::~SceneManager()
{
	for (Helheim::Scene* pScene : m_pScenes)
		DELETE_POINTER(pScene);
}

Helheim::Scene& Helheim::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_pScenes.push_back(scene);
	m_ActiveSceneIndex = (int)(m_pScenes.size() - 1);
	return *scene;
}
