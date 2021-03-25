#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

#include "Locator.h"
#include "Renderer.h"
#include <SDL.h>

using namespace Helheim;

unsigned int Scene::m_IdCounter = 0;

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

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (Helheim::GameObject* pGO : m_pObjects)
		DELETE_POINTER(pGO);
}

void Scene::Add(GameObject* object)
{
	m_pObjects.push_back(object);
}

void Scene::Update()
{
	for (GameObject* object : m_pObjects)
	{
		object->Update();
	}
}

void Helheim::Scene::FixedUpdate()
{
	for (GameObject* object : m_pObjects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	//auto renderer{ Helheim::Renderer::GetInstance().GetSDLRenderer() };
	auto renderer{ Locator::GetRendererService()->GetSDLRenderer() };
	SDL_RenderClear(renderer);
	for (const Helheim::GameObject* object : m_pObjects)
	{
		object->Render();
	}
	//Helheim::Renderer::GetInstance().RenderUI();
	Locator::GetRendererService()->RenderUI();
	SDL_RenderPresent(renderer);
}

