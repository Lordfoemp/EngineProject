#include "MiniGamePCH.h"
#include "QBERT.h"

#include "GameObject.h"
#include "Scene.h"

#include "TextureComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

#include "Locator.h"
#include "ResourceManager.h"


Helheim::QBERT::QBERT(const std::string& name)
		: m_Name(name)
		, m_pQBERTGO(nullptr)
		, m_pHealthGO(nullptr)
		, m_pScoreGO(nullptr)
{}

void Helheim::QBERT::Initialize(Scene* pCurrentScene, const glm::vec3& position)
{
	InitializeQBERT(pCurrentScene, position);
	//InitializeHealth(pCurrentScene);
	//InitializeScore(pCurrentScene);
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
	m_pQBERTGO->SetName("QBERT");

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
	m_pScoreGO->AddComponent(pTextComponent1);
	m_pScoreGO->SetName("Score UI");

	// Add to scene
	pCurrentScene->AddGameObject(m_pScoreGO);
}