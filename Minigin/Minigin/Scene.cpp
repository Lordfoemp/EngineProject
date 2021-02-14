#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"
#include <chrono>
#include <SDL.h>
using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	auto renderer{ dae::Renderer::GetInstance().GetSDLRenderer() };
	SDL_RenderClear(renderer);
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
	SDL_RenderPresent(renderer);

}

