#include "MiniGamePCH.h"
#include "QBERT.h"

#include "GameObject.h"

#include "Scene_01.h"
#include "Scene_02.h"
#include "Scene_03.h"
#include "Level.h"

#include <TextureComponent.h>
#include <HealthComponent.h>
#include <ScoreComponent.h>
#include <TextComponent.h>
#include <TransformComponent.h>
#include "JumpComponent.h"
#include "ColliderComponent.h"
#include <PhysicsComponent.h>


#include "Locator.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "Command.h"
#include "JumpCommand.h"
#include "EscapeCommand.h"

#include "Cube.h"
#include "Connection.h"
#include "Level.h"

#include "ScoreObserver.h"
#include "HealthObserver.h"
#include "ColliderObserver.h"
#include "DiscObserver.h"

// New
#include "QBERTComponent.h"


Helheim::QBERT::QBERT(const std::string& name)
			   : m_Name(name)
			   , m_pQBERTGO(nullptr)
			   , m_pHealthGO(nullptr)
			   , m_pScoreGO(nullptr)
			   , m_StartPosition()
{}
Helheim::QBERT::~QBERT()
{
	DELETE_POINTER(m_pQBERTGO);
	DELETE_POINTER(m_pScoreGO);
	DELETE_POINTER(m_pHealthGO);
}

void Helheim::QBERT::Initialize(const glm::vec3& position)
{
	InitializeQBERT(position);
	InitializeHealth();
	InitializeScore();
	InitializeInput();
}

void Helheim::QBERT::AddToScene(Scene* pCurrentScene, const int sceneIdx)
{
	if (sceneIdx == 1)
	{
		Scene_01* pScene{ dynamic_cast<Scene_01*>(pCurrentScene) };
		pScene->AddGameObject(m_pQBERTGO);
		pScene->AddGameObject(m_pScoreGO);
		pScene->AddGameObject(m_pHealthGO);
	}
	else if (sceneIdx == 2)
	{
		Scene_02* pScene{ dynamic_cast<Scene_02*>(pCurrentScene) };
		pScene->AddGameObject(m_pQBERTGO);
		pScene->AddGameObject(m_pScoreGO);
		pScene->AddGameObject(m_pHealthGO);
	}
	else if (sceneIdx == 3)
	{
		Scene_03* pScene{ dynamic_cast<Scene_03*>(pCurrentScene) };
		pScene->AddGameObject(m_pQBERTGO);
		pScene->AddGameObject(m_pScoreGO);
		pScene->AddGameObject(m_pHealthGO);
	}
	pCurrentScene->SetQbert(this);
}

void Helheim::QBERT::InitializeQBERT(const glm::vec3& position)
{
	m_StartPosition = position;

	// Parameters
	glm::vec3 position_Char = position;
	glm::vec3 rotation_Char = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale_Char = glm::vec3{ 1.99f, 1.99f, 1.99f };

	// GameObject
	m_pQBERTGO = new Helheim::GameObject(position_Char, rotation_Char, scale_Char);
	
	// Observer
	std::shared_ptr<Helheim::ColliderObserver> pColliderObserver = std::make_shared<Helheim::ColliderObserver>();
	std::shared_ptr<Helheim::DiscObserver> pDiscObserver = std::make_shared<Helheim::DiscObserver>();

	// Componenets
	Helheim::QBERTComponent* pQBERTComponent = new Helheim::QBERTComponent(m_pQBERTGO);

	Helheim::TextureComponent* pTextureComponent = new Helheim::TextureComponent("Qbert.png", "QBERT/", m_pQBERTGO);
	pTextureComponent->SetCanRenderComponent(true);
	Helheim::HealthComponent* pHealthComponent = new Helheim::HealthComponent(m_pQBERTGO, 10, 3);
	Helheim::JumpComponent* pJumpComponent = new Helheim::JumpComponent(m_pQBERTGO);
	Helheim::PhysicsComponent* pPhysicsComponent = new Helheim::PhysicsComponent(m_pQBERTGO);
	Helheim::ColliderComponent* pColliderComponent = new Helheim::ColliderComponent(m_pQBERTGO);
	pColliderComponent->AddObserver(pColliderObserver);
	pJumpComponent->AddObserver(pDiscObserver);
	m_pQBERTGO->AddComponent(pQBERTComponent);
	m_pQBERTGO->AddComponent(pTextureComponent);
	m_pQBERTGO->AddComponent(pHealthComponent);
	m_pQBERTGO->AddComponent(pJumpComponent);
	m_pQBERTGO->AddComponent(pPhysicsComponent);
	m_pQBERTGO->AddComponent(pColliderComponent);
	m_pQBERTGO->SetName(m_Name);

	pTextureComponent->UpdateRenderSettings(16, 16, 0);
}
void Helheim::QBERT::InitializeHealth()
{
	// Parameters
	glm::vec3 position_Health = glm::vec3{ 20, 30, 0 };
	glm::vec3 rotation_Health = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale_Health = glm::vec3{ 1,  1, 1 };

	Helheim::Font* pHealthFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", "", 20) };

	// GameObject
	m_pHealthGO = new Helheim::GameObject(position_Health, rotation_Health, scale_Health);

	// Componenets
	Helheim::TextComponent* pTextComponent0 = new Helheim::TextComponent(m_pHealthGO, "Lives left: 3", pHealthFont);
	m_pHealthGO->AddComponent(pTextComponent0);
	m_pHealthGO->SetName("Health UI");

	// Add to scene
	//pCurrentScene->AddGameObject(m_pHealthGO);

}
void Helheim::QBERT::InitializeScore()
{
	// Parameters
	glm::vec3 position_Health = glm::vec3{ 20, 60, 0 };
	glm::vec3 rotation_Health = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale_Health = glm::vec3{ 1,  1, 1 };

	Helheim::Font* pScoreFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", "", 20) };

	// GameObject
	m_pScoreGO = new Helheim::GameObject(position_Health, rotation_Health, scale_Health);

	std::shared_ptr<Helheim::ScoreObserver> pScoreObserver = std::make_shared<Helheim::ScoreObserver>(nullptr, nullptr);

	// Componenets
	Helheim::TextComponent* pTextComponent = new Helheim::TextComponent(m_pScoreGO, "Score: 0", pScoreFont);
	Helheim::ScoreComponent* pScoreComponent = new Helheim::ScoreComponent(m_pScoreGO);
	pScoreComponent->AddObserver(pScoreObserver);
	m_pScoreGO->AddComponent(pTextComponent);
	m_pScoreGO->AddComponent(pScoreComponent);
	m_pScoreGO->SetName("Score UI");

	// Add to scene
	//pCurrentScene->AddGameObject(m_pScoreGO);
}
void Helheim::QBERT::InitializeInput()
{
	InputManager* pInputManager{ Locator::GetInputService() };

	pInputManager->AddKeyToMap(ControllerButton::ButtonA, SDL_SCANCODE_SPACE, ButtonPressType::BUTTON_HOLD, "Escape", new EscapeCommand(m_pQBERTGO, nullptr, true, false));
	pInputManager->AddKeyToMap(ControllerButton::ButtonDown, SDL_SCANCODE_DOWN, ButtonPressType::BUTTON_RELEASED, "JumpLeftDown", new JumpCommand(m_pQBERTGO, nullptr, true, false));
	pInputManager->AddKeyToMap(ControllerButton::ButtonLeft, SDL_SCANCODE_LEFT, ButtonPressType::BUTTON_RELEASED, "JumpLeftUp", new JumpCommand(m_pQBERTGO, nullptr, true, true));
	pInputManager->AddKeyToMap(ControllerButton::ButtonRight, SDL_SCANCODE_RIGHT, ButtonPressType::BUTTON_RELEASED, "JumpRightDown", new JumpCommand(m_pQBERTGO, nullptr, false, false));
	pInputManager->AddKeyToMap(ControllerButton::ButtonUp, SDL_SCANCODE_UP, ButtonPressType::BUTTON_RELEASED, "JumpRightUp", new JumpCommand(m_pQBERTGO, nullptr, false, true));
}

void Helheim::QBERT::Reset(const glm::vec3& cubeStartPosition)
{
	m_pQBERTGO->GetComponent<JumpComponent>()->ResetCurrentCubeIndex();
	m_pQBERTGO->GetComponent<JumpComponent>()->ResetCurrentDiscIndex();
	m_pQBERTGO->GetComponent<ColliderComponent>()->SetTargetCubeIndex(0);
	m_pQBERTGO->GetComponent<TransformComponent>()->SetPosition(cubeStartPosition.x + 10, cubeStartPosition.y - 20, cubeStartPosition.z);
}