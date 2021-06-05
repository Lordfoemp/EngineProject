#include "MiniginPCH.h"
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
	for (Cube* pCube : m_pCubes)
		DELETE_POINTER(pCube);
	for (Disc* pDisc : m_pDiscs)
		DELETE_POINTER(pDisc);
}

void Helheim::LevelComponent::Initialize(Scene* pParentScene)
{
	const int windowWidth{ pParentScene->GetWindowWidth() };
	const int windowHeight{ pParentScene->GetWindowHeight() };
	const int windowWidth_Half{ windowWidth / 2 };
	const int windowHeight_Half{ windowHeight / 2 };

	// ------
	// Positions
	// ------
	const int startHeight{ 100 };
	int heightDiff{ 37 };
	int widthDiff_Neg{ 22 };
	int widthDiff_Pos{ 23 };

	// ---------
	// Positions
	// ---------
	//		Cubes
	// ---------
	std::vector<glm::vec3> positions_Cubes{};
	std::vector<glm::vec3> positions_Discs{};
	// Row 1	
	positions_Cubes.push_back({ windowWidth_Half                      , startHeight + (0 * heightDiff), 0 });	
	// Row 2											        
	positions_Cubes.push_back({ windowWidth_Half - widthDiff_Neg      , startHeight + (1 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + widthDiff_Pos      , startHeight + (1 * heightDiff), 0 });	
	// Row 3
	positions_Cubes.push_back({ windowWidth_Half - (2 * widthDiff_Pos), startHeight + (2 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half                      , startHeight + (2 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + (2 * widthDiff_Pos), startHeight + (2 * heightDiff), 0 });	
	// Row 4
	positions_Cubes.push_back({ windowWidth_Half - (3 * widthDiff_Neg), startHeight + (3 * heightDiff), 0 });
	positions_Cubes.push_back({ windowWidth_Half - (1 * widthDiff_Neg), startHeight + (3 * heightDiff), 0 });
	positions_Cubes.push_back({ windowWidth_Half + (1 * widthDiff_Pos), startHeight + (3 * heightDiff), 0 });
	positions_Cubes.push_back({ windowWidth_Half + (3 * widthDiff_Pos), startHeight + (3 * heightDiff), 0 });
	// Row 5
	positions_Cubes.push_back({ windowWidth_Half - (4 * widthDiff_Neg), startHeight + (4 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half - (2 * widthDiff_Neg), startHeight + (4 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half                      , startHeight + (4 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + (2 * widthDiff_Pos), startHeight + (4 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + (4 * widthDiff_Neg), startHeight + (4 * heightDiff), 0 });	
	// Row 6
	positions_Cubes.push_back({ windowWidth_Half - (5 * widthDiff_Neg), startHeight + (5 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half - (3 * widthDiff_Neg), startHeight + (5 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half - (1 * widthDiff_Neg), startHeight + (5 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + (1 * widthDiff_Pos), startHeight + (5 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + (3 * widthDiff_Pos), startHeight + (5 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + (5 * widthDiff_Neg), startHeight + (5 * heightDiff), 0 });	
	// Row 7
	positions_Cubes.push_back({ windowWidth_Half - (6 * widthDiff_Neg), startHeight + (6 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half - (4 * widthDiff_Neg), startHeight + (6 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half - (2 * widthDiff_Neg), startHeight + (6 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half                      , startHeight + (6 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + (2 * widthDiff_Pos), startHeight + (6 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + (4 * widthDiff_Pos), startHeight + (6 * heightDiff), 0 });	
	positions_Cubes.push_back({ windowWidth_Half + (6 * widthDiff_Neg), startHeight + (6 * heightDiff), 0 });
	// ---------
	//		Discs
	// ---------
	positions_Discs.push_back({ windowWidth_Half - (5 * widthDiff_Neg), startHeight + (4 * heightDiff), 0 });
	positions_Discs.push_back({ windowWidth_Half + (6 * widthDiff_Neg), startHeight + (4 * heightDiff), 0 });

	// ------
	// Cubes & Discs
	// ------
	const size_t nbrOfCubes{ positions_Cubes.size() };
	for (size_t i{}; i < nbrOfCubes; ++i)
	{
		Cube* pCube{ new Cube() };
		pCube->Initialize(pParentScene, positions_Cubes[i], m_FolderPath, new CubeObserver(pCube, nullptr, nullptr));
		m_pCubes.push_back(pCube);
	}
	const size_t nbrOfDiscs{ positions_Discs.size() };
	for (size_t j{}; j < nbrOfDiscs; ++j)
	{
		Disc* pDisc{ new Disc() };
		pDisc->Initialize(pParentScene, positions_Discs[j], m_FolderPath);
		m_pDiscs.push_back(pDisc);
	}

	// -----------
	// Connections
	// -----------
	Create_AddConnections();
}
void Helheim::LevelComponent::Update(const float elapsedSec)
{
	bool levelComplete{};
	bool gameComplete{};
	if (Locator::GetSceneService()->GetActiveSceneIndex() == 0)
		levelComplete = LevelDone(LevelNmr::Level01);
	else if (Locator::GetSceneService()->GetActiveSceneIndex() == 1)
		levelComplete = LevelDone(LevelNmr::Level02);
	else if (Locator::GetSceneService()->GetActiveSceneIndex() == 2)
		gameComplete = LevelDone(LevelNmr::Level03);

	if (levelComplete)
		m_pObservers[0]->OnNotify(m_pParentObject, Observer::OBSERVER_EVENTS::LOAD_NEXT_LEVEL);
	if (gameComplete)
		m_pObservers[0]->OnNotify(m_pParentObject, Observer::OBSERVER_EVENTS::LOAD_NEXT_LEVEL);

	{	// Update discs
		//GameObject* pPlayerGO = Locator::GetSceneService()->GetActiveScene()->GetObjectByName("Player 1");
		for (size_t i{}; i < m_pDiscs.size(); ++i)
		{
			Disc* pDisc{ m_pDiscs[i] };
			if (!pDisc->GetIsUsed())
				pDisc->Update(elapsedSec);
			else
			{
				//pPlayerGO->GetComponent<ColliderComponent>()->Reset();
				//Locator::GetSceneService()->GetActiveScene()->GetQBERT()->Reset(pDisc->GetGameObject()->GetComponent<TransformComponent>()->GetPosition());
			}
		}
	}
}
void Helheim::LevelComponent::FixedUpdate(const float)
{}

void Helheim::LevelComponent::Create_AddConnections()
{
	std::vector<Helheim::Connection*> connections{};
	size_t cubeIndex{0};
	// 0 - Connection cubes:	1, 2
	AddConnections_Cubes(cubeIndex, { 1, 2 });
	// 1 - Connection cubes:	  0, 3, 4
	AddConnections_Cubes(++cubeIndex, { 0, 3, 4 });
	// 2 - Connection cubes:	  0, 4, 5
	AddConnections_Cubes(++cubeIndex, { 0, 4, 5 });
	// 3 - Connection cubes:	  1, 7, 6
	AddConnections_Cubes(++cubeIndex, { 1, 7, 6 });
	// 4 - Connection cubes:	  1, 7, 8, 2
	AddConnections_Cubes(++cubeIndex, { 1, 7, 8, 2 });
	// 5 - Connection cubes: 	  2, 8, 9
	AddConnections_Cubes(++cubeIndex, { 2, 8, 9 });
	// 6 - Connection cubes: 	  3, 11, 10
	AddConnections_Cubes(++cubeIndex, { 3, 11, 10 });
	// 7 - Connection cubes: 	  3, 11, 12, 4
	AddConnections_Cubes(++cubeIndex, { 3, 11, 12, 4 });
	// 8 - Connection cubes: 	  4, 12, 13, 5
	AddConnections_Cubes(++cubeIndex, { 4, 12, 13, 5 });
	// 9 - Connection cubes: 	  5, 13, 14
	AddConnections_Cubes(++cubeIndex, { 5, 13, 14 });
	// 10 - Connection cubes: 	  6, 16, 15
	AddConnections_Cubes(++cubeIndex, { 6, 16, 15 });
	// 11 - Connection cubes: 	  6, 16, 17, 7
	AddConnections_Cubes(++cubeIndex, { 6, 16, 17, 7 });
	// 12 - Connection cubes: 	  7, 17, 18, 8
	AddConnections_Cubes(++cubeIndex, { 7, 17, 18, 8 });
	// 13 - Connection cubes: 	  8, 18, 19, 9
	AddConnections_Cubes(++cubeIndex, { 8, 18, 19, 9 });
	// 14 - Connection cubes: 	  9, 19, 20
	AddConnections_Cubes(++cubeIndex, { 9, 19, 20 });
	// 15 - Connection cubes: 	  10, 21, 22
	AddConnections_Cubes(++cubeIndex, { 10, 21, 22 });
	// 16 - Connection cubes: 	  10, 22, 23, 11
	AddConnections_Cubes(++cubeIndex, { 10, 22, 23, 11 });
	// 17 - Connection cubes: 	  11, 23, 24, 12
	AddConnections_Cubes(++cubeIndex, { 11, 23, 24, 12 });
	// 18 - Connection cubes: 	  12, 24, 25, 13
	AddConnections_Cubes(++cubeIndex, { 12, 24, 25, 13 });
	// 19 - Connection cubes: 	  13, 25, 26, 14	
	AddConnections_Cubes(++cubeIndex, { 13, 25, 26, 14 });
	// 20 - Connection cubes: 	  14, 26, 27
	AddConnections_Cubes(++cubeIndex, { 14, 26, 27 });
	// 21 - Connection cubes: 	  15 
	AddConnections_Cubes(++cubeIndex, { 15 });
	// 22 - Connection cubes: 	  15, 16
	AddConnections_Cubes(++cubeIndex, { 15, 16 });
	// 23 - Connection cubes: 	  16, 17
	AddConnections_Cubes(++cubeIndex, { 16, 17 });
	// 24 - Connection cubes: 	  17, 18
	AddConnections_Cubes(++cubeIndex, { 17, 18 });
	// 25 - Connection cubes: 	  18, 19
	AddConnections_Cubes(++cubeIndex, { 18, 19 });
	// 26 - Connection cubes: 	  19, 20
	AddConnections_Cubes(++cubeIndex, { 19, 20 });
	// 27 - Connection cubes: 	  20
	AddConnections_Cubes(++cubeIndex, { 20 });

	// 10 - Connection disc
	AddConnections_Discs(10, { 0 });
	// 14 - Connection disc
	AddConnections_Discs(14, { 1 });
}
void Helheim::LevelComponent::AddConnections_Cubes(size_t cubeToEdit, std::vector<size_t> connectionIDs)
{
	const size_t nbrOfConnections{ connectionIDs.size() };
	for (size_t i{}; i < nbrOfConnections; ++i)
		m_pCubes[cubeToEdit]->AddConnections(new Connection(m_pCubes[cubeToEdit], m_pCubes[connectionIDs[i]]));
}
void Helheim::LevelComponent::AddConnections_Discs(size_t cubeToEdit, std::vector<size_t> connectionIDs)
{
	const size_t nbrOfConnections{ connectionIDs.size() };
	for (size_t i{}; i < nbrOfConnections; ++i)
		m_pCubes[cubeToEdit]->AddConnections(new Connection(m_pCubes[cubeToEdit], m_pDiscs[connectionIDs[i]]));
}

bool Helheim::LevelComponent::LevelDone(const LevelNmr& levelNmr) const
{
	if (levelNmr == LevelNmr::Level01 || levelNmr == LevelNmr::Level03)
	{
		int counter{};
		for (Cube* pCube : m_pCubes)
		{
			if (pCube->GetStepOnCounter() == 1)
				counter++;
		}

		return (size_t(counter) == m_pCubes.size());
	}
	else if (levelNmr == LevelNmr::Level02)
	{
		int counter{};
		for (Cube* pCube : m_pCubes)
		{
			if (pCube->GetStepOnCounter() == 2)
				counter++;
		}

		return (size_t(counter) == m_pCubes.size());
	}

	return false;
}
bool Helheim::LevelComponent::ColorCube(const size_t index)
{
	Cube* pCube{ m_pCubes[index] };
	if (m_LevelNmr == LevelNmr::Level01 || m_LevelNmr == LevelNmr::Level02)
	{
		return pCube->ChangeColor(false);
	}
	if (m_LevelNmr == LevelNmr::Level03)
	{
		return pCube->ChangeColor(true);
	}

	return false;
}