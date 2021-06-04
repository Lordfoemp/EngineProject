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
#include "SceneManager.h"

#include <string>

Helheim::Cube::Cube()
	    : m_IsColored(false)
		, m_pCubeGO(nullptr)
		, m_pTexture_Base(nullptr)
		, m_pTexture_Colored_01(nullptr)
		, m_pTexture_Colored_02(nullptr)
		, m_pConnections(std::vector<Connection*>())
{}

void Helheim::Cube::Initialize(Scene* pCurrentScene, const glm::vec3& pos, const std::string& folderpath, Observer* pObserver)//pCurrentScene
{
	m_pObserver = pObserver;

	// Parameters
	glm::vec3 position = pos;
	glm::vec3 rotation = glm::vec3{ 0,  0, 0 };
	glm::vec3 scale = glm::vec3{ 1.5f, 1.5f, 1.5f };

	// GameObject
	m_pCubeGO = new Helheim::GameObject(position, rotation, scale);

	// Componenets
	m_pTexture_Base = new Helheim::TextureComponent("Cube_Base.png", folderpath, m_pCubeGO);
	m_pTexture_Colored_01 = new Helheim::TextureComponent("Cube_Colored_01.png", folderpath, m_pCubeGO);
	m_pTexture_Colored_01->SetCanRenderComponent(false);
	m_pCubeGO->AddComponent(m_pTexture_Base);
	m_pCubeGO->AddComponent(m_pTexture_Colored_01);
	if (folderpath.find('2') != std::string::npos)
	{
		m_pTexture_Colored_02 = new Helheim::TextureComponent("Cube_Colored_02.png", folderpath, m_pCubeGO);
		m_pTexture_Colored_02->SetCanRenderComponent(false);
		m_pCubeGO->AddComponent(m_pTexture_Colored_02);
	}
	
	m_pCubeGO->SetName("Cube");

	// Add to scene
	pCurrentScene->AddGameObject(m_pCubeGO);
}

bool Helheim::Cube::ChangeColor(bool )
{
	if (Locator::GetSceneService()->GetActiveSceneIndex() == 0)
	{
		// If the first texture is being renderd activate the next one
		if (m_pTexture_Base->CanRenderComponent())
		{
			return ChangeTextures(false, true, false);
		}
	}
	else if (Locator::GetSceneService()->GetActiveSceneIndex() == 1)
	{
		// If the first texture is being renderd activate the next one
		if (m_pTexture_Base->CanRenderComponent())
		{
			return ChangeTextures(false, true, false);
		}
		// If the second texture is being renderd activate the next one
		else if (m_pTexture_Colored_01->CanRenderComponent())
		{
			return ChangeTextures(false, false, true);
		}
	}
	else if (Locator::GetSceneService()->GetActiveSceneIndex() == 2)
	{
		// If the first texture is being renderd activate the next one
		if (m_pTexture_Base->CanRenderComponent())
		{
			return ChangeTextures(false, true, false);
		}
		// If the second texture is being renderd activate the next one
		else if (m_pTexture_Colored_01->CanRenderComponent())
		{
			return ChangeTextures(true, false, false);
		}
	}

	return false;
}

bool Helheim::Cube::ChangeTextures(const bool texture01, const bool texture02, const bool texture03)
{
	if (m_pTexture_Base)
		m_pTexture_Base->SetCanRenderComponent(texture01);
	if (m_pTexture_Colored_01)
		m_pTexture_Colored_01->SetCanRenderComponent(texture02);
	if (m_pTexture_Colored_02)
		m_pTexture_Colored_02->SetCanRenderComponent(texture03);
	
	if (texture01)
		m_StepOnCounter--;
	else
	{
		m_StepOnCounter++;	
		return true;
	}

	return false;
}