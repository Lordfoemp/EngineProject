#include "MiniGamePCH.h"
#include "LevelComponent.h"

// dae Includes
#include "GameObject.h"
#include "Scene.h"

// Helheim Includes
#include "Timer.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "../MiniGame/Cube.h"
#include "../MiniGame/Disc.h"
#include "../MiniGame/Connection.h"
#include "../MiniGame/CubeObserver.h"

#include "SceneManager.h"
#include "../MiniGame/QBERT.h"

#include "../MiniGame/LevelParser.h"

#include "CubeComponent.h"

Helheim::LevelComponent::LevelComponent(Helheim::GameObject* pParentObject, const glm::vec3& color, const std::string& folder, const LevelNmr& levelNmr)
						: Component(pParentObject, false)
						, m_StartColor(color)
						, m_CurrentColor(color)
						, m_Event(Observer::OBSERVER_EVENTS::NO_EVENT)
						, m_TouchedCubes(0)
						, m_FolderPath(folder)
						, m_LevelNmr(levelNmr)
{}
Helheim::LevelComponent::~LevelComponent()
{
	/*for (Cube* pCube : m_pCubes)
		DELETE_POINTER(pCube);
	for (Disc* pDisc : m_pDiscs)
		DELETE_POINTER(pDisc);*/
}

void Helheim::LevelComponent::Initialize(Scene* pParentScene)
{
	// Parsing
	using cubeToEdit = int;
	using connections = std::vector<int>;

	std::vector<glm::vec3> positions_Cubes{};
	std::vector<glm::vec3> positions_Discs{};
	std::vector<std::pair<cubeToEdit, connections>> connectionsToCubes{};
	std::vector<std::pair<cubeToEdit, connections>> connectionsToDiscs{};

	LevelParser parser{ "../Data/QBERT/Loading/Level.txt" };
	parser.ParseLevel(positions_Cubes, positions_Discs, connectionsToCubes, connectionsToDiscs);

	// ------
	// Cubes & Discs
	// ------
	const size_t nbrOfCubes{ positions_Cubes.size() };
	for (size_t i{}; i < nbrOfCubes; ++i)
	{
		Cube* pCube{ new Cube() };
		pCube->Initialize(pParentScene, positions_Cubes[i], m_FolderPath);
	}
	const size_t nbrOfDiscs{ positions_Discs.size() };
	for (size_t j{}; j < nbrOfDiscs; ++j)
	{
		Disc* pDisc{ new Disc() };
		pDisc->Initialize(pParentScene, positions_Discs[j], m_FolderPath);
	}

	
}
void Helheim::LevelComponent::PostInitialize(Scene* pParentScene)	//pParentScene
{
	// Parsing
	using cubeToEdit = int;
	using connections = std::vector<int>;

	std::vector<glm::vec3> positions_Cubes{};
	std::vector<glm::vec3> positions_Discs{};
	std::vector<std::pair<cubeToEdit, connections>> connectionsToCubes{};
	std::vector<std::pair<cubeToEdit, connections>> connectionsToDiscs{};

	LevelParser parser{ "../Data/QBERT/Loading/Level.txt" };
	parser.ParseLevel(positions_Cubes, positions_Discs, connectionsToCubes, connectionsToDiscs);

	std::vector<GameObject*> pObjects{ pParentScene->GetObjects() };
	for (GameObject* pGameObject : pObjects)
	{
		if (pGameObject->GetName() == "Cube")
			m_pCubes.push_back(pGameObject);
		else if (pGameObject->GetName() == "Disc")
			m_pDiscs.push_back(pGameObject);
	}

	// -----------
	// Connections
	// -----------
	Create_AddConnections(connectionsToCubes, connectionsToDiscs);
}
void Helheim::LevelComponent::Update(const float )
{
	bool levelComplete{};
	bool gameComplete{};
	if (Locator::GetSceneService()->GetActiveGameSceneIndex() == 0)
		levelComplete = LevelDone(LevelNmr::Level01);
	else if (Locator::GetSceneService()->GetActiveGameSceneIndex() == 1)
		levelComplete = LevelDone(LevelNmr::Level02);
	else if (Locator::GetSceneService()->GetActiveGameSceneIndex() == 2)
		gameComplete = LevelDone(LevelNmr::Level03);

	if (levelComplete)
		m_pObservers[0]->OnNotify(m_pParentObject, Observer::OBSERVER_EVENTS::LOAD_NEXT_LEVEL);
	if (gameComplete)
		m_pObservers[0]->OnNotify(m_pParentObject, Observer::OBSERVER_EVENTS::LOAD_NEXT_LEVEL);

	//{	// Update discs
	//	for (size_t i{}; i < m_pDiscs.size(); ++i)
	//	{
	//		Disc* pDisc{ m_pDiscs[i] };
	//		if (!pDisc->GetIsUsed())
	//			pDisc->Update(elapsedSec);
	//	}
	//}
}
void Helheim::LevelComponent::FixedUpdate(const float)
{}

void Helheim::LevelComponent::Create_AddConnections(std::vector<std::pair<int, std::vector<int>>>& connectionsToCubes, std::vector<std::pair<int, std::vector<int>>>& connectionsToDiscs)
{
	const size_t nbrOfConnectionToCubes{ connectionsToCubes.size() };
	for (size_t i{}; i < nbrOfConnectionToCubes; ++i)
	{
		std::pair<int, std::vector<int>> connectionsData{ connectionsToCubes[i] };
		AddConnections_Cubes(connectionsData.first, connectionsData.second);
	}
	const size_t nbrOfConnectionToDiscs{ connectionsToDiscs.size() };
	for (size_t j{}; j < nbrOfConnectionToDiscs; ++j)
	{
		std::pair<int, std::vector<int>> connectionsData{ connectionsToDiscs[j] };
		AddConnections_Discs(connectionsData.first, connectionsData.second);
	}
}
void Helheim::LevelComponent::AddConnections_Cubes(size_t cubeToEdit, std::vector<int> connectionIDs)
{
	const size_t nbrOfConnections{ connectionIDs.size() };
	for (size_t i{}; i < nbrOfConnections; ++i)
	{
		GameObject* pHead{ m_pCubes[cubeToEdit] };
		GameObject* pTail{ m_pCubes[connectionIDs[i]] };
		pHead->GetComponent<CubeComponent>()->AddConnections(new Connection(pHead, pTail, false));
	}
}
void Helheim::LevelComponent::AddConnections_Discs(size_t cubeToEdit, std::vector<int> connectionIDs)
{
	const size_t nbrOfConnections{ connectionIDs.size() };
	for (size_t i{}; i < nbrOfConnections; ++i)
	{
		GameObject* pHead{ m_pCubes[cubeToEdit] };
		GameObject* pTail{ m_pDiscs[connectionIDs[i]] };
		pHead->GetComponent<CubeComponent>()->AddConnections(new Connection(pHead, pTail, true));
	}
}

bool Helheim::LevelComponent::LevelDone(const LevelNmr& levelNmr) const
{
	if (levelNmr == LevelNmr::Level01 || levelNmr == LevelNmr::Level03)
	{
		int counter{};
		for (GameObject* pCube : m_pCubes)
		{
			if (pCube->GetComponent<CubeComponent>()->GetStepOnCounter() == 1)
				counter++;
		}

		return (size_t(counter) == m_pCubes.size());
	}
	else if (levelNmr == LevelNmr::Level02)
	{
		int counter{};
		for (GameObject* pCube : m_pCubes)
		{
			if (pCube->GetComponent<CubeComponent>()->GetStepOnCounter() == 2)
				counter++;
		}

		return (size_t(counter) == m_pCubes.size());
	}

	return false;
}
bool Helheim::LevelComponent::ColorCube(const size_t index)
{
	return m_pCubes[index]->GetComponent<CubeComponent>()->ChangeColor();
}