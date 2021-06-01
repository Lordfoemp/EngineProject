#include "MiniGamePCH.h"
#include "Level.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "Scene.h"
#include "GameObject.h"
#include "LevelComponent.h"
#include "Observers.h"

Helheim::Level::Level()
	: m_pLevelGO(nullptr)
	, m_pLevelComponent(nullptr)
{}

void Helheim::Level::Initialize(Scene * pCurrentScene)
{
	// Level - Cube
	glm::vec3 position = glm::vec3{ 400, 200, 0 };
	glm::vec3 rotation = glm::vec3{ 0,   0, 0 };
	glm::vec3 scale = glm::vec3{ 1,   1, 1 };

	m_pLevelGO = new Helheim::GameObject(position, rotation, scale);
	std::shared_ptr<Helheim::LevelObserver> pLevelObserver = std::make_shared<Helheim::LevelObserver>(nullptr, nullptr);
	m_pLevelComponent = new Helheim::LevelComponent(m_pLevelGO, glm::vec3(1, 0, 0));
	m_pLevelComponent->AddObserver(pLevelObserver);
	m_pLevelGO->AddComponent(m_pLevelComponent);
	m_pLevelGO->SetName("LevelCube");
	pCurrentScene->AddGameObject(m_pLevelGO);
}