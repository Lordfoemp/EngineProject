#include "MiniGamePCH.h"
#include "Cube.h"

#include "GameObject.h"
#include "Scene.h"

#include "TextureComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

#include "Locator.h"
#include "ResourceManager.h"

Helheim::Cube::Cube()
	    : m_IsColored(false)
		, m_pCubeGO(nullptr)
		, m_pTexture_Base(nullptr)
		, m_pTexture_Colored(nullptr)
{}

void Helheim::Cube::Initialize(Scene* pCurrentScene, const glm::vec3& pos)//pCurrentScene
{
	// Parameters
	//glm::vec3 position_Char = { position.x + 22, position.y - 10, position.z };
	glm::vec3 position = pos;
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale = glm::vec3{ 1.5f, 1.5f, 1.5f };

	// GameObject
	m_pCubeGO = new Helheim::GameObject(position, rotation, scale);

	// Componenets
	m_pTexture_Base = new Helheim::TextureComponent("Cube_Base.png", "QBERT/Level_01/", m_pCubeGO);
	m_pTexture_Colored = new Helheim::TextureComponent("Cube_Colored.png", "QBERT/Level_01/", m_pCubeGO);
	m_pCubeGO->AddComponent(m_pTexture_Base);
	m_pCubeGO->SetName("Cube");

	// Add to scene
	pCurrentScene->AddGameObject(m_pCubeGO);
}