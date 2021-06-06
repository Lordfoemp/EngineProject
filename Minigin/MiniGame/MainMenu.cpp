#include "MiniGamePCH.h"
#include "MainMenu.h"

#include "GameObject.h"
#include "TextureComponent.h"

#include "SceneManager.h"
#include "InputManager.h"

#include "PlayCommand.h"
#include "ControllsCommand.h"
#include "QuitCommand.h"

Helheim::MainMenu::MainMenu(const int windowWidth, const int windowHeight, const bool isActive)
				  : Scene(windowWidth, windowHeight, isActive)
				  , m_pMenuGO(nullptr)
				  , m_pTextureComponent_Base(nullptr)
				  , m_pTextureComponent_Play_Pressed(nullptr)
				  , m_pTextureComponent_Controls_Pressed(nullptr)
				  , m_pTextureComponent_Quit_Pressed(nullptr)

{}

void Helheim::MainMenu::Initialize()
{
	InitializeImage();
	InitializeButtons();
	InitializeInputs();

	Scene::Initialize();
}
void Helheim::MainMenu::PostInitialize()
{
}
void Helheim::MainMenu::Update(const float elapsedSec)
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	//std::cout << "Mouse position - x: " << x << '\n';
	//std::cout << "Mouse position - y: " << y << '\n';

	Scene::Update(elapsedSec);

	std::vector<Button> buttons{ GetButtons() };
	for (Button& button : buttons)
	{
		if (IsInsideButton({ x, y }, button))
		{
			DisableAllImages();
			button.pTextureComponent_Pressed->SetCanRenderComponent(true);			
		}
	}
}
void Helheim::MainMenu::FixedUpdate(const float timeEachUpdate)
{
	Scene::FixedUpdate(timeEachUpdate);
}
void Helheim::MainMenu::LateUpdate()
{
	Scene::LateUpdate();
}
void Helheim::MainMenu::Render() const
{
	Scene::Render();
}

void Helheim::MainMenu::InitializeImage()
{
	// Parameters
	glm::vec3 position = glm::vec3{ 0, 0, 0 };
	glm::vec3 rotation = glm::vec3{ 0, 0, 0 };
	glm::vec3 scale = glm::vec3{ 1.f, 1.f, 1.f };

	// GameObject
	m_pMenuGO = new GameObject();

	// Componenets
	m_pTextureComponent_Base = new Helheim::TextureComponent("Main_Menu_Normal.png", "QBERT/Menu/", m_pMenuGO);
	m_pTextureComponent_Play_Pressed = new Helheim::TextureComponent("Main_Menu_Play_Pressed.png", "QBERT/Menu/", m_pMenuGO);
	m_pTextureComponent_Controls_Pressed = new Helheim::TextureComponent("Main_Menu_Controls_Pressed.png", "QBERT/Menu/", m_pMenuGO);
	m_pTextureComponent_Quit_Pressed = new Helheim::TextureComponent("Main_Menu_Quit_Pressed.png", "QBERT/Menu/", m_pMenuGO);
	m_pTextureComponent_Base->SetCanRenderComponent(true);
	m_pMenuGO->AddComponent(m_pTextureComponent_Base);
	m_pMenuGO->AddComponent(m_pTextureComponent_Play_Pressed);
	m_pMenuGO->AddComponent(m_pTextureComponent_Controls_Pressed);
	m_pMenuGO->AddComponent(m_pTextureComponent_Quit_Pressed);

	m_pMenuGO->SetName("Disc");

	// Add to scene
	AddGameObject(m_pMenuGO);
}
void Helheim::MainMenu::InitializeButtons()
{
	// Boundaries
	/*			y
		/---------------\
		|				|
	x	|	  Button	| z
		|				|
		\---------------/
				w
	*/

	AddButton("Play", "Main_Menu_Play_Pressed", {571, 396, 619, 410}, m_pTextureComponent_Play_Pressed);
	AddButton("Controlls", "Main_Menu_Play_Pressed", { 517, 419, 619, 430 }, m_pTextureComponent_Controls_Pressed);
	AddButton("Quit", "Main_Menu_Play_Pressed", { 573, 443, 619, 458 }, m_pTextureComponent_Quit_Pressed);
}
void Helheim::MainMenu::InitializeInputs()
{
	InputManager* pInputManager{ Locator::GetInputService() };

	pInputManager->AddKeyToMap(ControllerButton::ButtonX, SDL_SCANCODE_X, ButtonPressType::BUTTON_RELEASED, "Play", new PlayCommand());
	pInputManager->AddKeyToMap(ControllerButton::ButtonY, SDL_SCANCODE_Y, ButtonPressType::BUTTON_RELEASED, "Controlls", new ControllsCommand());
	pInputManager->AddKeyToMap(ControllerButton::ButtonB, SDL_SCANCODE_B, ButtonPressType::BUTTON_RELEASED, "Quit", new QuitCommand());
} 

void Helheim::MainMenu::DisableAllImages()
{
	m_pTextureComponent_Base->SetCanRenderComponent(false);
	m_pTextureComponent_Play_Pressed->SetCanRenderComponent(false);
	m_pTextureComponent_Controls_Pressed->SetCanRenderComponent(false);
	m_pTextureComponent_Quit_Pressed->SetCanRenderComponent(false);
}

bool Helheim::MainMenu::IsInsideButton(const glm::vec2& currMousePos, const Button& button)
{
	if (button.Boundaries.x < currMousePos.x && currMousePos.x < button.Boundaries.z)
		if (button.Boundaries.y < currMousePos.y && currMousePos.y < button.Boundaries.w)
			return true;

	return false;
}