#include "MiniGamePCH.h"
#include "QBERT.h"

#include "GameObject.h"

#include "Scene_01.h"
#include "Scene_02.h"
#include "Scene_03.h"
#include "Level.h"

#include "TextureComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

#include "Locator.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "Command.h"

#include "Cube.h"
#include "Connection.h"
#include "Level.h"

#include "ScoreObserver.h"
#include "HealthObserver.h"

Helheim::QBERT::QBERT(const std::string& name)
			   : m_CurrentCubeIndex(0)
			   , m_Name(name)
			   , m_pQBERTGO(nullptr)
			   , m_pHealthGO(nullptr)
			   , m_pScoreGO(nullptr)
			   , m_StartPosition()
{}

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

	// Componenets
	m_pTextureComponent_Qbert_LeftDown = new Helheim::TextureComponent("QBERT_LeftDown.png", "QBERT/", m_pQBERTGO);
	m_pTextureComponent_Qbert_LeftDown->SetCanRenderComponent(false);
	m_pTextureComponent_Qbert_LeftUp = new Helheim::TextureComponent("QBERT_LeftUp.png", "QBERT/", m_pQBERTGO);
	m_pTextureComponent_Qbert_LeftUp->SetCanRenderComponent(false);
	m_pTextureComponent_Qbert_RightDown = new Helheim::TextureComponent("QBERT_RightDown.png", "QBERT/", m_pQBERTGO);
	m_pTextureComponent_Qbert_RightDown->SetCanRenderComponent(true);
	m_pTextureComponent_Qbert_RightUp = new Helheim::TextureComponent("QBERT_RightUp.png", "QBERT/", m_pQBERTGO);
	m_pTextureComponent_Qbert_RightUp->SetCanRenderComponent(false);
	Helheim::HealthComponent* pHealthComponent = new Helheim::HealthComponent(m_pQBERTGO, 10, 3);
	m_pQBERTGO->AddComponent(m_pTextureComponent_Qbert_LeftDown);
	m_pQBERTGO->AddComponent(m_pTextureComponent_Qbert_LeftUp);
	m_pQBERTGO->AddComponent(m_pTextureComponent_Qbert_RightDown);
	m_pQBERTGO->AddComponent(m_pTextureComponent_Qbert_RightUp);
	m_pQBERTGO->AddComponent(pHealthComponent);
	m_pQBERTGO->SetName(m_Name);
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

	//Scene_01* pScene{ dynamic_cast<Scene_01*>(pCurrentScene) };
	/*if (!pScene)
	{
		Scene_02* pScene2{ dynamic_cast<Scene_02*>(pCurrentScene) };

		pInputManager->AddKeyToMap(ControllerButton::ButtonDown, SDL_SCANCODE_DOWN, ButtonPressType::BUTTON_RELEASED, "JumpLeftDown", new JumpCommand(this, pScene2->GetLevelGO(), true, false));
		pInputManager->AddKeyToMap(ControllerButton::ButtonLeft, SDL_SCANCODE_LEFT, ButtonPressType::BUTTON_RELEASED, "JumpLeftUp", new JumpCommand(this, pScene2->GetLevelGO(), true, true));
		pInputManager->AddKeyToMap(ControllerButton::ButtonRight, SDL_SCANCODE_RIGHT, ButtonPressType::BUTTON_RELEASED, "JumpRightDown", new JumpCommand(this, pScene2->GetLevelGO(), false, false));
		pInputManager->AddKeyToMap(ControllerButton::ButtonUp, SDL_SCANCODE_UP, ButtonPressType::BUTTON_RELEASED, "JumpRightUp", new JumpCommand(this, pScene2->GetLevelGO(), false, true));

		return;
	}*/

	pInputManager->AddKeyToMap(ControllerButton::ButtonDown, SDL_SCANCODE_DOWN, ButtonPressType::BUTTON_RELEASED, "JumpLeftDown", new JumpCommand(this, nullptr, true, false));
	pInputManager->AddKeyToMap(ControllerButton::ButtonLeft, SDL_SCANCODE_LEFT, ButtonPressType::BUTTON_RELEASED, "JumpLeftUp", new JumpCommand(this, nullptr, true, true));
	pInputManager->AddKeyToMap(ControllerButton::ButtonRight, SDL_SCANCODE_RIGHT, ButtonPressType::BUTTON_RELEASED, "JumpRightDown", new JumpCommand(this, nullptr, false, false));
	pInputManager->AddKeyToMap(ControllerButton::ButtonUp, SDL_SCANCODE_UP, ButtonPressType::BUTTON_RELEASED, "JumpRightUp", new JumpCommand(this, nullptr, false, true));
}

void Helheim::QBERT::Jump(GameObject* , const bool jumpLeft, const bool jumpUp)
{
	// Get current data of QBERT
	TransformComponent* pTransformComponent{ m_pQBERTGO->GetComponent<TransformComponent>() };
	glm::vec3 currentPositionQBERT{ pTransformComponent->GetPosition() };

	// Retrieve the level from the Level Game Object
	LevelComponent* pLevelComponent{ nullptr };
	{
		Scene* pScene = Locator::GetSceneService()->GetActiveScene();
		Scene_01* pScene01{ dynamic_cast<Scene_01*>(pScene) };
		if (pScene01)
			pLevelComponent = pScene01->GetLevel()->GetLevelComponent();
		else
		{
			Scene_02* pScene02{ dynamic_cast<Scene_02*>(pScene) };
			if (pScene02)
				pLevelComponent = pScene02->GetLevel()->GetLevelComponent();
			else
			{
				Scene_03* pScene03{ dynamic_cast<Scene_03*>(pScene) };
				if (pScene03)
					pLevelComponent = pScene03->GetLevel()->GetLevelComponent();
			}
		}
	}

	// Get all the needed data for easy access
	std::vector<Cube*> pCubes = pLevelComponent->GetCubes();
	Cube* pCurrentCube{ pCubes[m_CurrentCubeIndex] };
	std::vector<Connection*> pConnections = pCurrentCube->GetConnections();

	// Find the connection that is on the left and lower then the player
	bool connectingCubeFound{ false };
	Connection* pConnection{ nullptr };
	Cube* pConnectingCube{ nullptr };
	glm::vec3 connectingCubePosition{};
	const size_t nbrOfConnection{ pConnections.size() };
	for (size_t i{}; i < nbrOfConnection; ++i)
	{
		pConnection = pConnections[i];

		// Check if the connecting cube is on the left, down of the QBERT
		pConnectingCube = pConnection->GetCube2();
		connectingCubePosition = pConnectingCube->GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
		
		// Disable all texture and enable the right one with the finding of a cube
		m_pTextureComponent_Qbert_LeftDown->SetCanRenderComponent(false);
		m_pTextureComponent_Qbert_LeftUp->SetCanRenderComponent(false);
		m_pTextureComponent_Qbert_RightDown->SetCanRenderComponent(false);
		m_pTextureComponent_Qbert_RightUp->SetCanRenderComponent(false);

		// Jump Left
		bool jumpLeftDown{ jumpLeft && !jumpUp};
		if (jumpLeftDown)
		{
			m_pTextureComponent_Qbert_LeftDown->SetCanRenderComponent(true);
			if (connectingCubePosition.x < currentPositionQBERT.x && connectingCubePosition.y > currentPositionQBERT.y + 20.f)
			{
				connectingCubeFound = true;
				break;
			}
		}
		bool jumpLeftUp{ jumpLeft && jumpUp };
		if (jumpLeftUp)
		{
			m_pTextureComponent_Qbert_LeftUp->SetCanRenderComponent(true);
			if (currentPositionQBERT.x > connectingCubePosition.x && currentPositionQBERT.y + 20.f > connectingCubePosition.y)
			{
				connectingCubeFound = true;
				break;
			}
		}
		// Jump Right
		bool jumpRightDown{ !jumpLeft && !jumpUp };
		if (jumpRightDown)
		{
			m_pTextureComponent_Qbert_RightDown->SetCanRenderComponent(true);
			if (currentPositionQBERT.x < connectingCubePosition.x && connectingCubePosition.y > currentPositionQBERT.y + 20.f)
			{
				connectingCubeFound = true;
				break;
			}
		}
		bool jumpRightUp{ !jumpLeft && jumpUp };
		if (jumpRightUp)
		{
			m_pTextureComponent_Qbert_RightUp->SetCanRenderComponent(true);
			if (currentPositionQBERT.x < connectingCubePosition.x && currentPositionQBERT.y + 20.f > connectingCubePosition.y)
			{
				connectingCubeFound = true;
				break;
			}
		}
	}

	if (connectingCubeFound)
	{
		// Set the new current index of the new cube
		m_CurrentCubeIndex = std::distance(pCubes.begin(), std::find(pCubes.begin(), pCubes.end(), pConnectingCube));
		std::cout << "Current cube index: " << m_CurrentCubeIndex << '\n';

		// Set the QBERT position to the new position and update the m_CurrentCubeIndex	
		pTransformComponent->SetPosition(connectingCubePosition.x + 10, connectingCubePosition.y - 20, 0);	

		if (!pConnectingCube->GetIsColored())
		{
			// Change Color
			pConnectingCube->ChangeColor();
			/*pLevelComponent->IncreaseTouchedCubes();
			std::cout << "Touched cubes: " << pLevelComponent->GetNbrOfTouchedCubes() << '\n';*/
			m_pScoreGO->GetComponent<ScoreComponent>()->IncreaseScore(25);
		}			
	}
}

void Helheim::QBERT::Reset(const glm::vec3& cubeStartPosition)
{
	m_CurrentCubeIndex = 0;
	m_pQBERTGO->GetComponent<TransformComponent>()->SetPosition(cubeStartPosition.x + 10, cubeStartPosition.y - 20, cubeStartPosition.z);
}