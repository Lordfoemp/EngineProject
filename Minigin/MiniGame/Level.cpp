#include "MiniGamePCH.h"
#include "Level.h"

#include "Scene.h"
#include "GameObject.h"
#include "LevelComponent.h"
#include "LevelObserver.h"
#include <string>

Helheim::Level::Level()
	: m_pLevelGO(nullptr)
	, m_pLevelComponent(nullptr)
{}

void Helheim::Level::Initialize(Scene * pCurrentScene, const std::string& folder, const LevelComponent::LevelNmr& levelNmr)
{
	// Level - Cube
	glm::vec3 position = glm::vec3{ 400, 200, 0 };
	glm::vec3 rotation = glm::vec3{ 0,   0, 0 };
	glm::vec3 scale = glm::vec3{ 1,   1, 1 };

	m_pLevelGO = new Helheim::GameObject(position, rotation, scale);
	m_pLevelComponent = new Helheim::LevelComponent(m_pLevelGO, glm::vec3(1, 0, 0), folder, levelNmr);
	std::shared_ptr<Helheim::LevelObserver> pLevelObserver = std::make_shared<Helheim::LevelObserver>(m_pLevelGO, nullptr);
	m_pLevelComponent->AddObserver(pLevelObserver);
	m_pLevelGO->AddComponent(m_pLevelComponent);
	m_pLevelGO->SetName("LevelCube");
	pCurrentScene->AddGameObject(m_pLevelGO);
}