#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

#include "Locator.h"
#include "Renderer.h"
//#include <SDL.h>

Helheim::Scene::Scene(const int windowWidth, const int windowHeight)
	    : m_WindowWidth(windowWidth)
	    , m_WindowHeight(windowHeight)
	    , m_Name("")
	    , m_pObjects(std::vector<GameObject*>())
{}
Helheim::Scene::~Scene()
{
	for (Helheim::GameObject* pGO : m_pObjects)
		DELETE_POINTER(pGO);
}

void Helheim::Scene::Initialize()
{
	for (GameObject* object : m_pObjects)
		if (object)
			object->Initialize();
}
void Helheim::Scene::Update(const float elapsedSec)
{
	for (GameObject* object : m_pObjects)
		object->Update(elapsedSec);
}
void Helheim::Scene::FixedUpdate(const float timeEachUpdate)
{
	for (GameObject* object : m_pObjects)
		object->FixedUpdate(timeEachUpdate);
}
void Helheim::Scene::LateUpdate()
{
	
}
void Helheim::Scene::Render() const
{
	SDL_Renderer* renderer{ Locator::GetRendererService()->GetSDLRenderer() };
	SDL_RenderClear(renderer);
	for (const Helheim::GameObject* object : m_pObjects)
	{
		object->Render();
	}
	//Locator::GetRendererService()->RenderUI();
	SDL_RenderPresent(renderer);
}


void Helheim::Scene::AddGameObject(GameObject* object)
{
	object->SetParentScene(this);
	m_pObjects.push_back(object);
}
Helheim::GameObject* Helheim::Scene::GetObjectByName(const std::string& name) const
{
	for (Helheim::GameObject* pGameObject : m_pObjects)
	{
		if (pGameObject)
			if (pGameObject->GetName() == name)
				return pGameObject;
	}
	return nullptr;
}