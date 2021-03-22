#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"
#include <chrono>
#include <SDL.h>
using namespace Helheim;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>&object)
{
	m_pObjects.push_back(object);
}

void Scene::Update()
{
	for (std::shared_ptr<GameObject>& object : m_pObjects)
	{
		object->Update();
	}
}

void Helheim::Scene::FixedUpdate()
{
	for (std::shared_ptr<GameObject>& object : m_pObjects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	//auto renderer{ Helheim::Renderer::GetInstance().GetSDLRenderer() };
	auto renderer{ Locator::GetRendererService()->GetSDLRenderer() };
	SDL_RenderClear(renderer);
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
	//Helheim::Renderer::GetInstance().RenderUI();
	Locator::GetRendererService()->RenderUI();
	SDL_RenderPresent(renderer);

}

