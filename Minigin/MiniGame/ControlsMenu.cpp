#include "MiniGamePCH.h"
#include "ControlsMenu.h"

#include "GameObject.h"
#include "TextureComponent.h"

#include "BackCommand.h"

#include "SceneManager.h"
#include "InputManager.h"

Helheim::ControlsMenu::ControlsMenu(const int windowWidth, const int windowHeight, const bool isActive)
					  : Scene(windowWidth, windowHeight, isActive)
					  , m_pMenuGO(nullptr)
					  , m_pTextureComponent_Base(nullptr)
					  , m_pTextureComponent_Back_Pressed(nullptr)
{}

void Helheim::ControlsMenu::Initialize()
{
	InitializeImage();
	InitializeButtons();
	InitializeInputs();

	Scene::Initialize();
}
void Helheim::ControlsMenu::PostInitialize()
{
}
void Helheim::ControlsMenu::Update(const float elapsedSec)
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
void Helheim::ControlsMenu::FixedUpdate(const float timeEachUpdate)
{
	Scene::FixedUpdate(timeEachUpdate);
}
void Helheim::ControlsMenu::LateUpdate()
{
	Scene::LateUpdate();
}
void Helheim::ControlsMenu::Render() const
{
	Scene::Render();
}

void Helheim::ControlsMenu::InitializeImage()
{
	// Parameters
	glm::vec3 position = glm::vec3{ 0, 0, 0 };
	glm::vec3 rotation = glm::vec3{ 0, 0, 0 };
	glm::vec3 scale = glm::vec3{ 1.f, 1.f, 1.f };

	// GameObject
	m_pMenuGO = new GameObject();

	// Componenets
	m_pTextureComponent_Base = new Helheim::TextureComponent("Controls_Menu_Normal.png", "QBERT/Menu/", m_pMenuGO);
	m_pTextureComponent_Back_Pressed = new Helheim::TextureComponent("Controls_Menu_Back_Pressed.png", "QBERT/Menu/", m_pMenuGO);
	m_pTextureComponent_Base->SetCanRenderComponent(true);
	m_pMenuGO->AddComponent(m_pTextureComponent_Base);
	m_pMenuGO->AddComponent(m_pTextureComponent_Back_Pressed);

	m_pMenuGO->SetName("Disc");

	// Add to scene
	AddGameObject(m_pMenuGO);
}
void Helheim::ControlsMenu::InitializeButtons()
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

	AddButton("Back", "Controls_Menu_Back_Pressed", {557, 439, 624, 460}, m_pTextureComponent_Back_Pressed);
}
void Helheim::ControlsMenu::InitializeInputs()
{
	InputManager* pInputManager{ Locator::GetInputService() };

	pInputManager->AddKeyToMap(ControllerButton::ButtonStart, SDL_SCANCODE_ESCAPE, ButtonPressType::BUTTON_RELEASED, "Back", new BackCommand());
}

void Helheim::ControlsMenu::DisableAllImages()
{
	m_pTextureComponent_Base->SetCanRenderComponent(false);
	m_pTextureComponent_Back_Pressed->SetCanRenderComponent(false);
}

bool Helheim::ControlsMenu::IsInsideButton(const glm::vec2& currMousePos, const Button& button)
{
	if (button.Boundaries.x < currMousePos.x && currMousePos.x < button.Boundaries.z)
		if (button.Boundaries.y < currMousePos.y && currMousePos.y < button.Boundaries.w)
			return true;

	return false;
}