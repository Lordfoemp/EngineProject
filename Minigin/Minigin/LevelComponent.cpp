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