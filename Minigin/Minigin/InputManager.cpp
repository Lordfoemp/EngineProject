#include "MiniginPCH.h"
#pragma comment(lib, "XInput.lib")
#include "InputManager.h"

#include "Command.h"
#include "Timer.h"
#include "Observer.h"

#include  <typeinfo> 

Helheim::InputManager::InputManager()
{}
Helheim::InputManager::~InputManager()
{
	for (std::pair<ControllerButton, std::pair<Key, Command*>> command : m_ControllerScheme)
	{
		std::pair<Key, Command*> pair{ m_ControllerScheme[command.first] };
		delete pair.second;
		pair.second = nullptr;
	}
}

bool Helheim::InputManager::ProcessInput(const float elapsedSec)
{
	// Zero out the controller state & get the current controller state
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);
	// Zero out the keyboard state & get the current keyboard state
	ZeroMemory(&m_KeyboardKeysState, sizeof(Uint8));
	m_KeyboardKeysState = SDL_GetKeyboardState(NULL);

	if (ProcessSDLInput())
	{
		ProcessAllControllerScheme();
		UpdateOldButton(elapsedSec);

		return true;
	}	

	return false;
}

bool Helheim::InputManager::IsButtonDown(const Key& key)
{
	ControllerButton controllerButton{ key.controllerButton };
	//SDL_Scancode keyboardButton{ key.keyboardButton };

	if (WORD(controllerButton) & m_CurrentState.Gamepad.wButtons)
		return true;
	return false;
}
bool Helheim::InputManager::IsButtonPressed(const Key& key)
{
	bool isPressed{ IsButtonDown(key) };
	if (isPressed && m_Oldbutton != key.controllerButton)
	{
		m_Oldbutton = key.controllerButton;
		return true;
	}
	return false;
}
bool Helheim::InputManager::IsButtonReleased(const Key& key)
{
	bool isPressed{ IsButtonDown(key) };
	bool releasedButton{ false };
	while (isPressed)
	{
		// Zero out the controller state & get the current controller state
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(0, &m_CurrentState);
		// Zero out the keyboard state & get the current keyboard state
		ZeroMemory(&m_KeyboardKeysState, sizeof(Uint8));
		m_KeyboardKeysState = SDL_GetKeyboardState(NULL);

		isPressed = IsButtonDown(key);
		if (!isPressed)
			releasedButton = true;
	}

	return releasedButton;
}

void Helheim::InputManager::ProcessAllControllerScheme()
{
	for (const std::pair<const Helheim::ControllerButton, std::pair<Helheim::Key, Helheim::Command*>>& pair : m_ControllerScheme)
	{
		Helheim::Command* pCommand{ nullptr };
		bool executeCommand{ false };
		const std::pair<Helheim::Key, Helheim::Command*> controllSecond{ pair.second };
		if (controllSecond.first.buttonState == ButtonPressType::BUTTON_HOLD)
		{
			if (IsButtonDown(controllSecond.first))
			{
				//std::cout << "Button - held down \n";
				executeCommand = true;
			}
		}
		else if (controllSecond.first.buttonState == ButtonPressType::BUTTON_PRESSED)
		{
			if (IsButtonPressed(controllSecond.first))
			{
				//std::cout << "Button - pressed \n";
				executeCommand = true;
			}
		}
		else if (controllSecond.first.buttonState == ButtonPressType::BUTTON_RELEASED)
		{
			if (IsButtonReleased(controllSecond.first))
			{
				//std::cout << "Button - released \n";
				executeCommand = true;
			}
		}
		
		if (executeCommand)
		{
			pCommand = GetCommand(controllSecond.first.controllerButton);
			pCommand->Execute();
		}
	}
}
bool Helheim::InputManager::ProcessSDLInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		Command* pCommand{ nullptr };
		bool executeCommand{ false };
		for (const std::pair<const Helheim::ControllerButton, std::pair<Helheim::Key, Helheim::Command*>>& pair : m_ControllerScheme)
		{
			const std::pair<Helheim::Key, Helheim::Command*> controllSecond{ pair.second };
			if (controllSecond.first.buttonState == ButtonPressType::BUTTON_HOLD && event.type == SDL_KEYDOWN)
			{
				if (int(event.key.keysym.scancode) == controllSecond.first.keyboardButton)
					executeCommand = true;
			}
			else if (controllSecond.first.buttonState == ButtonPressType::BUTTON_PRESSED &&  event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				if (int(event.key.keysym.scancode) == controllSecond.first.keyboardButton)
					executeCommand = true;
			}
			else if (controllSecond.first.buttonState == ButtonPressType::BUTTON_RELEASED && event.type == SDL_KEYUP)
			{
				if (int(event.key.keysym.scancode) == controllSecond.first.keyboardButton)
					executeCommand = true;
			}		

			if (executeCommand)
			{
				pCommand = GetCommand(controllSecond.first.controllerButton);
				pCommand->Execute();

				return true;
			}
			
		}

		if (event.type == SDL_QUIT)
		{
			return false;
		}
	}

	return true;
}
void Helheim::InputManager::UpdateOldButton(const float elapsedSec)
{
	if (m_Oldbutton != ControllerButton::NoAction)
	{
		if (m_CurrentTimer_OldButton <= m_MaxTimer_OldButton)
			m_CurrentTimer_OldButton += elapsedSec;
		else
		{
			m_CurrentTimer_OldButton = 0;
			m_Oldbutton = ControllerButton::NoAction;
		}
	}
}

void Helheim::InputManager::AddKeyToMap(const ControllerButton& cButton, const SDL_Scancode& kButton, const ButtonPressType& pressType, const std::string& name, Command* const pCommand)
{
	Key key{};
	key.controllerButton = cButton;
	key.keyboardButton = kButton;
	key.buttonState = pressType;
	key.commandName = name;
	
	std::pair<Key, Command*> key_command{ std::make_pair(key, pCommand) };
	m_ControllerScheme.emplace(cButton, std::move(key_command));
}
void Helheim::InputManager::EditKeyInMap()
{
	std::cout << "Editiitititititiititit \n";

	LOG_ENDLINE("| ------------- |");
	LOG_ENDLINE("> EditButtons - <");
	LOG_ENDLINE("| ------------- |");

	LOG_ENDLINE("Which button do you want for the following actions:");

	for (const std::pair<const Helheim::ControllerButton, std::pair<Helheim::Key, Helheim::Command*>>& pair : m_ControllerScheme)
	{
		const std::pair<Helheim::Key, Helheim::Command*> controllSecond{ pair.second };
		LOG_ENDLINE("Which buttons do you want for the following action?");
		LOG_ENDLINE(controllSecond.first.commandName);

		// CATCH the wanted input button

	}

























}

// Retrieve the command from a Controller button
Helheim::Command* Helheim::InputManager::GetCommand(const ControllerButton& cButton)
{ return m_ControllerScheme[cButton].second; }
// Retrieve the command from a Keyboard button
Helheim::Command* Helheim::InputManager::GetCommand(const SDL_Scancode& cButton)
{	
	for (std::pair<const Helheim::ControllerButton, std::pair<Helheim::Key, Helheim::Command*>>& pair : m_ControllerScheme)
	{
		std::pair<Helheim::Key, Helheim::Command*> controllSecond{ pair.second };
		if (controllSecond.first.keyboardButton == cButton)
			return controllSecond.second;
	}

	return nullptr;
}