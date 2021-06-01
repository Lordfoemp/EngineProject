#include "MiniGamePCH.h"
#include "QBERT.h"

#include "GameObject.h"

#include "Scene.h"
#include "Scene_01.h"

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

Helheim::QBERT::QBERT(const std::string& name)
			   : m_CurrentCubeIndex(0)
			   , m_Name(name)
			   , m_pQBERTGO(nullptr)
			   , m_pHealthGO(nullptr)
			   , m_pScoreGO(nullptr)
{}

void Helheim::QBERT::Initialize(Scene* pCurrentScene, const glm::vec3& position)
{
	InitializeQBERT(pCurrentScene, position);
	//InitializeHealth(pCurrentScene);
	InitializeScore(pCurrentScene);
	InitializeInput(pCurrentScene);
}

void Helheim::QBERT::InitializeQBERT(Scene* pCurrentScene, const glm::vec3& position)
{
	// Parameters
	glm::vec3 position_Char = position;
	glm::vec3 rotation_Char = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale_Char = glm::vec3{ 0.1f, 0.1f, 0.1f };

	// GameObject
	m_pQBERTGO = new Helheim::GameObject(position_Char, rotation_Char, scale_Char);

	// Componenets
	Helheim::TextureComponent* pTextureComponent = new Helheim::TextureComponent("Qbert.png", "QBERT/", m_pQBERTGO);
	Helheim::HealthComponent* pHealthComponent = new Helheim::HealthComponent(m_pQBERTGO, 10, 3);
	Helheim::ScoreComponent* pScoreComponent = new Helheim::ScoreComponent(m_pQBERTGO);
	m_pQBERTGO->AddComponent(pTextureComponent);
	m_pQBERTGO->AddComponent(pHealthComponent);
	m_pQBERTGO->AddComponent(pScoreComponent);
	m_pQBERTGO->SetName(m_Name);

	// Add to scene
	pCurrentScene->AddGameObject(m_pQBERTGO);
}
void Helheim::QBERT::InitializeHealth(Scene* pCurrentScene)
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
	pCurrentScene->AddGameObject(m_pHealthGO);

}
void Helheim::QBERT::InitializeScore(Scene* pCurrentScene)
{
	// Parameters
	glm::vec3 position_Health = glm::vec3{ 20, 30, 0 };
	glm::vec3 rotation_Health = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale_Health = glm::vec3{ 1,  1, 1 };

	Helheim::Font* pScoreFont{ Locator::GetResourceService()->LoadFont("Lingua.otf", "", 20) };

	// GameObject
	m_pScoreGO = new Helheim::GameObject(position_Health, rotation_Health, scale_Health);

	// Componenets
	Helheim::TextComponent* pTextComponent1 = new Helheim::TextComponent(m_pScoreGO, "Score: 0", pScoreFont);
	Helheim::ScoreComponent* pScoreComponent1 = new Helheim::ScoreComponent(m_pScoreGO);
	m_pScoreGO->AddComponent(pTextComponent1);
	m_pScoreGO->AddComponent(pScoreComponent1);
	m_pScoreGO->SetName("Score UI");

	// Add to scene
	pCurrentScene->AddGameObject(m_pScoreGO);
}
void Helheim::QBERT::InitializeInput(Scene* pCurrentScene)
{
	Scene_01* pScene{ static_cast<Scene_01*>(pCurrentScene) };

	InputManager* pInputManager{ Locator::GetInputService() };	
	pInputManager->AddKeyToMap(ControllerButton::ButtonDown, SDL_SCANCODE_DOWN, ButtonPressType::BUTTON_RELEASED, "JumpLeftDown", new JumpCommand(this, pScene->GetLevelGO(), true, false));
	pInputManager->AddKeyToMap(ControllerButton::ButtonLeft, SDL_SCANCODE_LEFT, ButtonPressType::BUTTON_RELEASED, "JumpLeftUp", new JumpCommand(this, pScene->GetLevelGO(), true, true));
	pInputManager->AddKeyToMap(ControllerButton::ButtonRight, SDL_SCANCODE_RIGHT, ButtonPressType::BUTTON_RELEASED, "JumpRightDown", new JumpCommand(this, pScene->GetLevelGO(), false, false));
	pInputManager->AddKeyToMap(ControllerButton::ButtonUp, SDL_SCANCODE_UP, ButtonPressType::BUTTON_RELEASED, "JumpRightUp", new JumpCommand(this, pScene->GetLevelGO(), false, true));
}

void Helheim::QBERT::Jump(GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp)
{
	// Get current data of QBERT
	TransformComponent* pTransformComponent{ m_pQBERTGO->GetComponent<TransformComponent>() };
	glm::vec3 currentPositionQBERT{ pTransformComponent->GetPosition() };

	// Retrieve the level from the Level Game Object
	LevelComponent* pLevelComponent{ pLevelGO->GetComponent<LevelComponent>() };

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
		
		// Jump Left
		bool jumpLeftDown{ jumpLeft && !jumpUp};
		if (jumpLeftDown)
		{
			if (connectingCubePosition.x < currentPositionQBERT.x && connectingCubePosition.y > currentPositionQBERT.y + 20.f)
			{
				connectingCubeFound = true;
				break;
			}
		}
		bool jumpLeftUp{ jumpLeft && jumpUp };
		if (jumpLeftUp)
		{
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
			if (currentPositionQBERT.x < connectingCubePosition.x && connectingCubePosition.y > currentPositionQBERT.y + 20.f)
			{
				connectingCubeFound = true;
				break;
			}
		}
		bool jumpRightUp{ !jumpLeft && jumpUp };
		if (jumpRightUp)
		{
			if (currentPositionQBERT.x < connectingCubePosition.x && currentPositionQBERT.y + 20.f > connectingCubePosition.y)
			{
				connectingCubeFound = true;
				break;
			}
		}
	}

	if (connectingCubeFound)
	{
		if (!pConnectingCube->GetIsColored())
		{
			// Change Color
			pConnectingCube->ChangeColor();
			pLevelComponent->IncreaseTouchedCubes();
			std::cout << "Touched cubes: " << pLevelComponent->GetNbrOfTouchedCubes() << '\n';
			m_pScoreGO->GetComponent<ScoreComponent>()->IncreaseScore(25);
		}

		// Set the new current index of the new cube
		m_CurrentCubeIndex = std::distance(pCubes.begin(), std::find(pCubes.begin(), pCubes.end(), pConnectingCube));
		std::cout << "Current cube index: " << m_CurrentCubeIndex << '\n';

		// Set the QBERT position to the new position and update the m_CurrentCubeIndex	
		pTransformComponent->SetPosition(connectingCubePosition.x - 17.5f, connectingCubePosition.y - 40, 0);		
	}
}