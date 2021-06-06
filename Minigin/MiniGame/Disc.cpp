#include "MiniGamePCH.h"
#include "Disc.h"

#include "Locator.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "DiscComponent.h"
#include "GameObject.h"
#include "QBERT.h"
#include "DiscObserver.h"

Helheim::Disc::Disc()
			  : m_Height(10)
			  , m_Width(16)
			  , m_pDiscGO(nullptr)
			  , m_pTexture_01(nullptr)
{}

void Helheim::Disc::Initialize(Scene * pCurrentScene, const glm::vec3 & pos, const std::string & folderpath)
{
	// Parameters
	glm::vec3 position = pos;
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale = glm::vec3{ 1.5f, 1.5f, 1.5f };

	// GameObject
	m_pDiscGO = new Helheim::GameObject(position, rotation, scale);

	// Observers
	std::shared_ptr<Helheim::DiscObserver> pDiscObserver = std::make_shared<Helheim::DiscObserver>();

	// Componenets
	Helheim::DiscComponent* pDiscComponent = new DiscComponent(m_pDiscGO);
	pDiscComponent->AddObserver(pDiscObserver);
	m_pTexture_01 = new Helheim::TextureComponent("Disc_01.png", folderpath, m_pDiscGO);
	m_pTexture_01->SetCanRenderComponent(true);
	m_pDiscGO->AddComponent(pDiscComponent);
	m_pDiscGO->AddComponent(m_pTexture_01);

	m_pDiscGO->SetName("Disc");

	// Add to scene
	pCurrentScene->AddGameObject(m_pDiscGO);
}