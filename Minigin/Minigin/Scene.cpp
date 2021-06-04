#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

#include "Locator.h"
#include "Renderer.h"
#include "TransformComponent.h"
//#include <SDL.h>

#include "../MiniGame/QBERT.h"

Helheim::Scene::Scene(const int windowWidth, const int windowHeight, const bool isActive)
	    : m_WindowWidth(windowWidth)
	    , m_WindowHeight(windowHeight)
	    , m_Name("")
	    , m_pObjects(std::vector<GameObject*>())
	    , m_IsActive(isActive)
	    , m_pQBERT(nullptr)
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
	if (!m_IsActive)
		return;

	for (GameObject* object : m_pObjects)
		object->Update(elapsedSec);
}
void Helheim::Scene::FixedUpdate(const float timeEachUpdate)
{
	if (!m_IsActive)
		return;

	for (GameObject* object : m_pObjects)
		object->FixedUpdate(timeEachUpdate);
}
void Helheim::Scene::LateUpdate()
{
	if (!m_IsActive)
		return;
}
void Helheim::Scene::Render() const
{
	if (!m_IsActive)
		return;

	SDL_Renderer* renderer{ Locator::GetRendererService()->GetSDLRenderer() };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderClear(renderer);
	for (const Helheim::GameObject* object : m_pObjects)
	{
		object->Render();
	}
	//Locator::GetRendererService()->RenderUI();
	
	{	// Collision shit
		const float size{ 30.f };
		glm::vec3 m_Rect = { size, size, 0 };
		glm::vec3 m_Pos = { GetQBERT()->GetGameObject_QBERT_Char()->GetComponent<TransformComponent>()->GetPosition() };

		SDL_SetRenderDrawColor(renderer, (Uint8)0, (Uint8)255.f, (Uint8)255.f, 1);
		SDL_Rect rect{ (int)m_Pos.x, (int)m_Pos.y, (int)m_Rect.x, (int)m_Rect.y };
		SDL_RenderDrawRect(renderer, &rect);
	}

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