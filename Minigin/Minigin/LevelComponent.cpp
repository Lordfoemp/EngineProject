#include "MiniginPCH.h"
#include "LevelComponent.h"

// dae Includes
#include "GameObject.h"
#include "Scene.h"

// Helheim Includes
#include "Timer.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"
#include "../MiniGame/Cube.h"
#include "../MiniGame/Connection.h"

Helheim::LevelComponent::LevelComponent(Helheim::GameObject* pParentObject, const glm::vec3& color)
						: Component(pParentObject, false)
						, m_StartColor(color)
						, m_CurrentColor(color)
						, m_Event(Observer::OBSERVER_EVENTS::NO_EVENT)
{
	/*if (!pParentObject->HasComponent<Helheim::TextureComponent>())
	{
		m_pTextureComponent = new Helheim::TextureComponent("Cube_Base.png", "QBERT/Level_01/", pParentObject);
		pParentObject->AddComponent(m_pTextureComponent);
	}
	else
		m_pTextureComponent = pParentObject->GetComponent<Helheim::TextureComponent>();*/
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
	std::vector<glm::vec3> positions{};
	// Row 1	
	positions.push_back({ windowWidth_Half                      , startHeight + (0 * heightDiff), 0 });	
	// Row 2											        
	positions.push_back({ windowWidth_Half + widthDiff_Pos      , startHeight + (1 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - widthDiff_Neg      , startHeight + (1 * heightDiff), 0 });	
	// Row 3
	positions.push_back({ windowWidth_Half                      , startHeight + (2 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half + (2 * widthDiff_Pos), startHeight + (2 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (2 * widthDiff_Pos), startHeight + (2 * heightDiff), 0 });	
	// Row 4
	positions.push_back({ windowWidth_Half + (1 * widthDiff_Pos), startHeight + (3 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (1 * widthDiff_Neg), startHeight + (3 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half + (3 * widthDiff_Pos), startHeight + (3 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (3 * widthDiff_Neg), startHeight + (3 * heightDiff), 0 });	
	// Row 5
	positions.push_back({ windowWidth_Half                      , startHeight + (4 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (2 * widthDiff_Neg), startHeight + (4 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half + (2 * widthDiff_Pos), startHeight + (4 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (4 * widthDiff_Neg), startHeight + (4 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half + (4 * widthDiff_Neg), startHeight + (4 * heightDiff), 0 });	
	// Row 6
	positions.push_back({ windowWidth_Half + (1 * widthDiff_Pos), startHeight + (5 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (1 * widthDiff_Neg), startHeight + (5 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half + (3 * widthDiff_Pos), startHeight + (5 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (3 * widthDiff_Neg), startHeight + (5 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half + (5 * widthDiff_Neg), startHeight + (5 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (5 * widthDiff_Neg), startHeight + (5 * heightDiff), 0 });	
	// Row 7
	positions.push_back({ windowWidth_Half                      , startHeight + (6 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half + (2 * widthDiff_Pos), startHeight + (6 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (2 * widthDiff_Neg), startHeight + (6 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half + (4 * widthDiff_Pos), startHeight + (6 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (4 * widthDiff_Neg), startHeight + (6 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half + (6 * widthDiff_Neg), startHeight + (6 * heightDiff), 0 });	
	positions.push_back({ windowWidth_Half - (6 * widthDiff_Neg), startHeight + (6 * heightDiff), 0 });	

	// ------
	// Cubes
	// ------
	const size_t nbrOfCubes{ positions.size() };
	for (size_t i{}; i < nbrOfCubes; ++i)
	{
		Cube* pCube{ new Cube() };
		pCube->Initialize(pParentScene, positions[i]);
		m_pCubes.push_back(pCube);
	}

	// -----------
	// Connections
	// -----------
	Create_AddConnections();
}
void Helheim::LevelComponent::Update(const float)
{
	if (m_StartColor != m_CurrentColor)
	{
		NotifyObservers(m_pParentObject, m_Event);
	}
}
void Helheim::LevelComponent::FixedUpdate(const float)
{}

void Helheim::LevelComponent::Create_AddConnections()
{
	std::vector<Helheim::Connection*> connections{};
	size_t cubeIndex{0};
	// 0 - Connection cubes: 1, 2
	AddConnections(cubeIndex, { 1, 2 });
	// 1 - Connection cubes: 0, 2, 3, 4
	AddConnections(++cubeIndex, { 0, 2, 3, 4 });
	// 2 - Connection cubes: 0, 1, 4, 5
	AddConnections(++cubeIndex, { 0, 1, 4, 5 });
	// 3 - Connection cubes: 1, 4, 7, 6
	AddConnections(++cubeIndex, { 1, 4, 7, 6 });
	// 4 - Connection cubes: 1, 3, 7, 8, 5, 2
	AddConnections(++cubeIndex, { 1, 3, 7, 8, 5, 2 });
	// 5 - Connection cubes: 2, 4, 8, 9
	AddConnections(++cubeIndex, { 2, 4, 8, 9 });
	// 6 - Connection cubes: 3, 7, 11, 10
	AddConnections(++cubeIndex, { 3, 7, 11, 10 });
	// 7 - Connection cubes: 3, 6, 11, 12, 8, 4
	AddConnections(++cubeIndex, { 3, 6, 11, 12, 8, 4 });
	// 8 - Connection cubes: 4, 7, 12, 13, 9, 5
	AddConnections(++cubeIndex, { 4, 7, 12, 13, 9, 5 });
	// 9 - Connection cubes: 5, 8, 13, 14
	AddConnections(++cubeIndex, { 5, 8, 13, 14 });
	// 10 - Connection cubes: 6, 11, 16, 15
	AddConnections(++cubeIndex, { 6, 11, 16, 15 });
	// 11 - Connection cubes: 6, 10, 16, 17, 12, 7
	AddConnections(++cubeIndex, { 6, 10, 16, 17, 12, 7 });
	// 12 - Connection cubes: 7, 11, 17, 18, 13, 8
	AddConnections(++cubeIndex, { 7, 11, 17, 18, 13, 8 });
	// 13 - Connection cubes: 8, 12, 18, 19, 14, 9
	AddConnections(++cubeIndex, { 8, 12, 18, 19, 14, 9 });
	// 14 - Connection cubes: 9, 13, 19, 20
	AddConnections(++cubeIndex, { 9, 13, 19, 20 });
	// 15 - Connection cubes: 10, 16, 21, 22
	AddConnections(++cubeIndex, { 10, 16, 21, 22 });
	// 16 - Connection cubes: 10, 15, 22, 23, 17, 11
	AddConnections(++cubeIndex, { 10, 15, 22, 23, 17, 11 });
	// 17 - Connection cubes: 11, 16, 23, 24, 18, 12
	AddConnections(++cubeIndex, { 11, 16, 23, 24, 18, 12 });
	// 18 - Connection cubes: 12, 17, 24, 25, 19, 13
	AddConnections(++cubeIndex, { 12, 17, 24, 25, 19, 13 });
	// 19 - Connection cubes: 13, 18, 25, 26, 20, 14	
	AddConnections(++cubeIndex, { 13, 18, 25, 26, 20, 14 });
	// 20 - Connection cubes: 14, 19, 26, 27
	AddConnections(++cubeIndex, { 14, 19, 26, 27 });
	// 21 - Connection cubes: 15, 22 
	AddConnections(++cubeIndex, { 15, 22 });
	// 22 - Connection cubes: 15, 21, 16, 23
	AddConnections(++cubeIndex, { 15, 21, 16, 23 });
	// 23 - Connection cubes: 22, 16, 17, 24
	AddConnections(++cubeIndex, { 22, 16, 17, 24 });
	// 24 - Connection cubes: 23, 17, 18, 25
	AddConnections(++cubeIndex, { 23, 17, 18, 25 });
	// 25 - Connection cubes: 24, 18, 19, 26
	AddConnections(++cubeIndex, { 24, 18, 19, 26 });
	// 26 - Connection cubes: 25, 19, 20, 27
	AddConnections(++cubeIndex, { 25, 19, 20, 27 });
	// 27 - Connection cubes: 26, 20
	AddConnections(++cubeIndex, { 26, 20 });
}
void Helheim::LevelComponent::AddConnections(size_t cubeToEdit, std::vector<size_t> connectionIDs)
{
	const size_t nbrOfConnections{ connectionIDs.size() };
	for (size_t i{}; i < nbrOfConnections; ++i)
		m_pCubes[cubeToEdit]->AddConnections(new Connection(m_pCubes[cubeToEdit], m_pCubes[connectionIDs[i]]));
}