#include "MiniGamePCH.h"
#include "Cube.h"

#include "GameObject.h"
#include "Scene.h"

#include "CubeComponent.h"
#include <TextureComponent.h>

#include "Locator.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#include <string>
#include "Connection.h"

Helheim::Cube::Cube()
	    : m_IsColored(false)
		, m_pCubeGO(nullptr)
		, m_pConnections(std::vector<Connection*>())
{}
Helheim::Cube::~Cube()
{
	//DELETE_POINTER(m_pObserver);
	for (Connection* pConnection : m_pConnections)
	{
		DELETE_POINTER(pConnection);
	}
}

void Helheim::Cube::Initialize(Scene* pCurrentScene, const glm::vec3& pos, const std::string& folderpath)// pCurrentScene // pObserver
{
	// Parameters
	glm::vec3 position = pos;
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale = glm::vec3{ 1.5f, 1.5f, 1.5f };

	// GameObject
	m_pCubeGO = new Helheim::GameObject(position, rotation, scale);

	// Componenets
	Helheim::CubeComponent* pCubeComponent = new CubeComponent(m_pCubeGO);
	Helheim::TextureComponent* pTextureComponent = new Helheim::TextureComponent("Cube.png", folderpath, m_pCubeGO);
	m_pCubeGO->AddComponent(pCubeComponent);
	m_pCubeGO->AddComponent(pTextureComponent);

	m_pCubeGO->SetName("Cube");

	// Add to scene
	pCurrentScene->AddGameObject(m_pCubeGO);

	pTextureComponent->UpdateRenderSettings(32, 32, 0);
}