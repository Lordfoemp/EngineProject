#include "MiniginPCH.h"
#pragma comment(lib, "XInput.lib")
#include "InputManager.h"

//#include <iostream>

#include "Command.h"
#include "Timer.h"
#include "Observer.h"

//#include <SDL.h>

//Helheim::InputManager::InputManager()
//    : m_CurrentButton(ControllerButton::NoAction)
//    , m_PreviousButton(ControllerButton::ButtonStart)
//    , m_CurrentChangeButton(ControllerButton::NoAction)
//    , m_PreviousChangeButton(ControllerButton::ButtonStart)
//    , m_ControllerState()
//    , m_Vibration()
//    , m_PreviousButtonResetTime(0.5f)
//    , m_PreviousButtonCurrentTime()
//{
//    DWORD dwResult;
//    dwResult = XInputGetState(0, &m_ControllerState);
//    if (dwResult == ERROR_SUCCESS)
//    {
//        m_ThumbStick_StartVals.push_back(m_ControllerState.Gamepad.sThumbLX / 32768.f);
//        m_ThumbStick_StartVals.push_back(m_ControllerState.Gamepad.sThumbLY / 32768.f);
//        m_ThumbStick_StartVals.push_back(m_ControllerState.Gamepad.sThumbRX / 32768.f);
//        m_ThumbStick_StartVals.push_back(m_ControllerState.Gamepad.sThumbRY / 32768.f);
//    }
//
//    SetupButtonMap();
//    SetupButtonOutputMap();
//
//    PrintOutputs();
//}
//Helheim::InputManager::~InputManager()
//{
//    for (std::pair<ControllerButton, std::pair<Command*, ButtonPressType>> command : m_pCommandsMap)
//    {
//        auto pair{ m_pCommandsMap[command.first] };
//        delete pair.first;
//        m_pCommandsMap[command.first].first = nullptr;
//    }
//}
//
//bool Helheim::InputManager::ProcessInput(const float elapsedSec)
//{
//    XINPUT_KEYSTROKE keyStroke{};
//
//    // todo: read the input
//    DWORD dwResult;
//    dwResult = XInputGetState(0, &m_ControllerState);
//
//    bool continueUpdateLoop{ false };
//    continueUpdateLoop = ProcessKeyboard_MouseInputs();
//    if (!continueUpdateLoop)
//        return false;
//
//    continueUpdateLoop = ProcessControllerInputs(dwResult, elapsedSec);
//    if (!continueUpdateLoop)
//        return false;
//
//    return true;
//}
//
//bool Helheim::InputManager::IsPressed(ControllerButton button) const
//{
//    return (m_CurrentButton == button);
//}
//
//void Helheim::InputManager::ConfigureButtons()
//{
//    bool keepChecking{ true };
//    LOG_ENDLINE("| ------------- |");
//    LOG_ENDLINE("> EditButtons - <");
//    LOG_ENDLINE("| ------------- |");
//
//    LOG_ENDLINE("Which button do you want for the following actions:");
//
//    UpdateButtonForAction("Jump: ", new JumpCommand(), keepChecking, ButtonPressType::BUTTON_UP);
//    keepChecking = true;
//    UpdateButtonForAction("Fire: ", new FireCommand(), keepChecking, ButtonPressType::BUTTON_HOLD);
//    keepChecking = true;
//    UpdateButtonForAction("Duck: ", new DuckCommand(), keepChecking, ButtonPressType::BUTTON_HOLD);
//    keepChecking = true;
//    UpdateButtonForAction("Fart: ", new FartCommand(), keepChecking, ButtonPressType::BUTTON_UP);
//}
//
//void Helheim::InputManager::UpdateButtonForAction(const std::string& actionName, Command* pCommand, bool& keepChecking, const ButtonPressType& buttonPressType)
//{
//    LOG_ENDLINE("Press the button you want for: ");
//    LOG(actionName);
//    while (keepChecking)
//    {
//        ControllerButton buttonToAssign{ GetButtonChoice(keepChecking) };
//        if (!keepChecking)
//        {
//            std::map<Helheim::ControllerButton, std::pair<Helheim::Command*, Helheim::ButtonPressType>>::iterator it = m_pCommandsMap.find(buttonToAssign);
//            if (it != m_pCommandsMap.end())
//            {
//                delete it->second.first;
//                it->second.first = nullptr;
//
//                it->second.first = pCommand;
//                it->second.second = buttonPressType;
//            }
//        }
//    }
//}
//Helheim::ControllerButton Helheim::InputManager::GetButtonChoice(bool& keepChecking)
//{
//    DWORD dwResult;
//    dwResult = XInputGetState(0, &m_ControllerState);
//
//    XINPUT_GAMEPAD* pGamePad = &m_ControllerState.Gamepad;
//    if (pGamePad->wButtons & XINPUT_GAMEPAD_A)
//    {
//        if (SetButtons(true, ControllerButton::ButtonA, ButtonPressType::BUTTON_UP))
//            keepChecking = false;
//    }
//    if (pGamePad->wButtons & XINPUT_GAMEPAD_B)
//    {
//        if (SetButtons(true, ControllerButton::ButtonB, ButtonPressType::BUTTON_UP))
//            keepChecking = false;
//    }
//    if (pGamePad->wButtons & XINPUT_GAMEPAD_X)
//    {
//        if (SetButtons(true, ControllerButton::ButtonX, ButtonPressType::BUTTON_UP))
//            keepChecking = false;
//    }
//    if (pGamePad->wButtons & XINPUT_GAMEPAD_Y)
//    {
//        if (SetButtons(true, ControllerButton::ButtonY, ButtonPressType::BUTTON_UP))
//            keepChecking = false;
//    }
//
//    return m_CurrentChangeButton;
//}
//
//void Helheim::InputManager::SetupButtonMap()
//{
//    ControllerButton key{};
//    std::pair<Command*, ButtonPressType> pair{};
//
//    // -----------------
//    // Buttons: A/B/X/Y
//    // -----------------
//    key = ControllerButton::ButtonA;
//    pair = std::make_pair<Command*, ButtonPressType>(new DieCommand(Helheim::Observer::OBSERVER_EVENTS::PLAYER_DIED_P1), ButtonPressType::BUTTON_UP);
//    m_pCommandsMap.emplace(key, pair);
//    key = ControllerButton::ButtonB;
//    pair = std::make_pair<Command*, ButtonPressType>(new ColorChangeCommand(Helheim::Observer::OBSERVER_EVENTS::COLOR_CHANGE_P1), ButtonPressType::BUTTON_UP);
//    m_pCommandsMap.emplace(key, pair);
//    key = ControllerButton::ButtonX;
//    pair = std::make_pair<Command*, ButtonPressType>(new DieCommand(Helheim::Observer::OBSERVER_EVENTS::PLAYER_DIED_P2), ButtonPressType::BUTTON_UP);
//    m_pCommandsMap.emplace(key, pair);
//    key = ControllerButton::ButtonY;
//    pair = std::make_pair<Command*, ButtonPressType>(new ColorChangeCommand(Helheim::Observer::OBSERVER_EVENTS::COLOR_CHANGE_P2), ButtonPressType::BUTTON_UP);
//    m_pCommandsMap.emplace(key, pair);
//
//    // ------------------
//    // Buttons: Triggers
//    // ------------------
//    key = ControllerButton::ButtonLTrigger;
//    pair = std::make_pair<Command*, ButtonPressType>(new DriveCommand("backward"), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//    key = ControllerButton::ButtonRTrigger;
//    pair = std::make_pair<Command*, ButtonPressType>(new DriveCommand("forward"), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//
//    // ----------------------
//    // Buttons: Thumb sticks
//    // ----------------------
//    key = ControllerButton::ButtonLThumbStick;
//    pair = std::make_pair<Command*, ButtonPressType>(new MoveCommand(), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//    key = ControllerButton::ButtonRThumbStick;
//    pair = std::make_pair<Command*, ButtonPressType>(new AimCommand(), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//
//    // -------------------
//    // Buttons: Shoulders
//    // -------------------
//    key = ControllerButton::ButtonLShoulder;
//    pair = std::make_pair<Command*, ButtonPressType>(new ScopeCommand(), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//    key = ControllerButton::ButtonRShoulder;
//    pair = std::make_pair<Command*, ButtonPressType>(new ShootCommand(), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//
//    // ----------------
//    // Buttons: Arrows
//    // ----------------
//    key = ControllerButton::ButtonUp;
//    pair = std::make_pair<Command*, ButtonPressType>(new ScrollInventoryCommand(false, false, true, false), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//    key = ControllerButton::ButtonDown;
//    pair = std::make_pair<Command*, ButtonPressType>(new ScrollInventoryCommand(false, false, false, true), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//    key = ControllerButton::ButtonLeft;
//    pair = std::make_pair<Command*, ButtonPressType>(new ScrollInventoryCommand(true, false, false, false), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//    key = ControllerButton::ButtonRight;
//    pair = std::make_pair<Command*, ButtonPressType>(new ScrollInventoryCommand(false, true, false, false), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//
//    // -------------------
//    // Buttons: No button
//    // -------------------
//    key = ControllerButton::NoAction;
//    pair = std::make_pair<Command*, ButtonPressType>(new NULLCommand(), ButtonPressType::BUTTON_HOLD);
//    m_pCommandsMap.emplace(key, pair);
//}
//void Helheim::InputManager::SetupButtonOutputMap()
//{
//    m_pCommandNamesMap.emplace(std::make_pair<ControllerButton, std::string>(ControllerButton::ButtonA, "ButtonA"));
//    m_pCommandNamesMap.emplace(std::make_pair<ControllerButton, std::string>(ControllerButton::ButtonB, "ButtonB"));
//    m_pCommandNamesMap.emplace(std::make_pair<ControllerButton, std::string>(ControllerButton::ButtonX, "ButtonX"));
//    m_pCommandNamesMap.emplace(std::make_pair<ControllerButton, std::string>(ControllerButton::ButtonY, "ButtonY"));
//
//    m_pCommandNamesMap.emplace(std::make_pair<ControllerButton, std::string>(ControllerButton::NoAction, "NoAction"));
//}
//
//// --------------------------
//// HOW TO
//// --------------------------
//void Helheim::InputManager::PrintOutputs()
//{
//    std::cout << "+<===============================================>+\n";
//    std::cout << "|<----------------------------------------------->|\n";
//    std::cout << "|| OBSERVER Assignement: Steve Verhoeven - 2DAE02||\n";
//    std::cout << "|<----------------------------------------------->|\n";
//    std::cout << "|<----------------------------------------------->|\n";
//    std::cout << "||                Input keys                     ||\n";
//    std::cout << "|<----------------------------------------------->|\n";
//    std::cout << "||-General---------------------------------------||\n";
//    std::cout << "|| Change buttons:   START                       ||\n";
//    std::cout << "|| Stop application: BACK                        ||\n";
//    std::cout << "|<----------------------------------------------->|\n";
//    std::cout << "||-Commands--------------------------------------||\n";
//    std::cout << "|| PLAYER 1                                      ||\n";
//    std::cout << "||-----------------------------------------------||\n";
//    std::cout << "|| DIE  : A                                      ||\n";
//    std::cout << "|| SCORE: B                                      ||\n";
//    std::cout << "||-----------------------------------------------||\n";
//    std::cout << "|| PLAYER 1                                      ||\n";
//    std::cout << "||-----------------------------------------------||\n";
//    std::cout << "|| DIE  : X                                      ||\n";
//    std::cout << "|| SCORE: Y                                      ||\n";
//    std::cout << "|<----------------------------------------------->|\n";
//    std::cout << "+<===============================================>+\n";
//}
//
//// ---------------------------
//// Keyboard & mouse OP stuffs
//// ---------------------------
//bool Helheim::InputManager::ProcessKeyboard_MouseInputs()
//{
//    SDL_Event e;
//    while (SDL_PollEvent(&e))
//    {
//        if (e.type == SDL_QUIT)
//        {
//            return false;
//        }
//        if (e.type == SDL_KEYDOWN)
//        {
//
//        }
//        if (e.type == SDL_MOUSEBUTTONDOWN)
//        {
//
//        }
//    }
//
//    return true;
//}
//
//// ----------------------
//// Controller stuffs
//// ----------------------
//bool Helheim::InputManager::ProcessControllerInputs(const DWORD& dwResult, const float elapsedSec)
//{
//    if (dwResult == ERROR_SUCCESS)
//    {
//        if (m_PreviousButtonCurrentTime >= m_PreviousButtonResetTime && m_PreviousButton != ControllerButton::NoAction)
//        {
//            m_PreviousButtonCurrentTime = 0;
//            m_PreviousButton = ControllerButton::NoAction;
//        }
//        else if (m_PreviousButton != ControllerButton::NoAction)
//            m_PreviousButtonCurrentTime += elapsedSec;
//
//        bool executeCommand{ false };
//        bool returnCommand{ true };
//        XINPUT_GAMEPAD* pGamePad = &m_ControllerState.Gamepad;
//
//        ProcessTriggers(pGamePad);
//        ProcessThumbSticks(pGamePad, executeCommand);
//        if (!executeCommand)
//            returnCommand = ProcessButtons(pGamePad, executeCommand);
//
//        if (executeCommand)
//            m_pCommandsMap[m_CurrentButton].first->Execute();
//
//        return returnCommand;
//    }
//    else
//    {
//        LOG_ENDLINE("Controller is not connected");
//        return true;
//        //return false;
//    }
//}
//void Helheim::InputManager::ProcessTriggers(XINPUT_GAMEPAD* pGamePad)
//{
//    auto leftTriggValue{ pGamePad->bLeftTrigger / 255.f };
//    if (leftTriggValue > 0)
//        m_pCommandsMap[ControllerButton::ButtonLTrigger].first->Execute();
//    auto rightTriggValue{ pGamePad->bRightTrigger / 255.f };
//    if (rightTriggValue > 0)
//        m_pCommandsMap[ControllerButton::ButtonRTrigger].first->Execute();
//}
//void Helheim::InputManager::ProcessThumbSticks(XINPUT_GAMEPAD* pGamePad, bool& executeCommand)
//{
//    const float THUMBSTICK_DEADZONE_LEFT{ XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE / 32768.f };
//    const float THUMBSTICK_DEADZONE_RIGHT{ XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE / 32768.f };
//
//    const float ThumbLX = pGamePad->sThumbLX / 32768.f;
//    const float ThumbLY = pGamePad->sThumbLY / 32768.f;
//    const float ThumbRX = pGamePad->sThumbRX / 32768.f;
//    const float ThumbRY = pGamePad->sThumbRY / 32768.f;
//
//    // Check the LEFT thumbstick
//    float differenceX{}, differenceY{};
//    float lowerBound_X{ m_ThumbStick_StartVals[0] - THUMBSTICK_DEADZONE_RIGHT };
//    float upperBound_X{ m_ThumbStick_StartVals[0] + THUMBSTICK_DEADZONE_RIGHT };
//    float lowerBound_Y{ m_ThumbStick_StartVals[1] - THUMBSTICK_DEADZONE_RIGHT };
//    float upperBound_Y{ m_ThumbStick_StartVals[1] + THUMBSTICK_DEADZONE_RIGHT };
//    if (ThumbLX < lowerBound_X || ThumbLX > upperBound_X ||
//        ThumbLY < lowerBound_Y || ThumbLY > upperBound_Y)
//    {
//        // If the left stick moved further then its deadzone in 1 of its axis
//        if (ThumbLX < lowerBound_X)
//            differenceX = ThumbLX - lowerBound_X;
//        else if (ThumbLX > upperBound_X)
//            differenceX = ThumbLX - upperBound_X;
//        if (ThumbLY < lowerBound_Y)
//            differenceY = ThumbLY - lowerBound_Y;
//        else if (ThumbLY > upperBound_Y)
//            differenceY = ThumbLY - lowerBound_Y;
//
//        m_CurrentButton = ControllerButton::ButtonLThumbStick;
//        dynamic_cast<MoveCommand*>(m_pCommandsMap[m_CurrentButton].first)->SetDirection({ differenceX, differenceY });
//        executeCommand = true;
//    }
//
//    // Check the RIGHT thumbstick
//    lowerBound_X = { m_ThumbStick_StartVals[2] - THUMBSTICK_DEADZONE_RIGHT };
//    upperBound_X = { m_ThumbStick_StartVals[2] + THUMBSTICK_DEADZONE_RIGHT };
//    lowerBound_Y = { m_ThumbStick_StartVals[3] - THUMBSTICK_DEADZONE_RIGHT };
//    upperBound_Y = { m_ThumbStick_StartVals[3] + THUMBSTICK_DEADZONE_RIGHT };
//    if (ThumbRX < lowerBound_X || ThumbRX > upperBound_X ||
//        ThumbRY < lowerBound_Y || ThumbRY > upperBound_Y)
//    {
//        // If the right stick moved further then its deadzone in 1 of its axis
//        if (ThumbRX < lowerBound_X)
//            differenceX = ThumbRX - lowerBound_X;
//        else if (ThumbRX > upperBound_X)
//            differenceX = ThumbRX - upperBound_X;
//        if (ThumbRY < lowerBound_Y)
//            differenceY = ThumbRY - lowerBound_Y;
//        else if (ThumbRY > upperBound_Y)
//            differenceY = ThumbRY - lowerBound_Y;
//
//        m_CurrentButton = ControllerButton::ButtonRThumbStick;
//        dynamic_cast<AimCommand*>(m_pCommandsMap[m_CurrentButton].first)->SetDirection({ differenceX, differenceY });
//        executeCommand = true;
//    }
//}
//bool Helheim::InputManager::ProcessButtons(XINPUT_GAMEPAD* pGamePad, bool& executeCommand)
//{
//    /* A - B - X - Y */
//    if (pGamePad->wButtons & XINPUT_GAMEPAD_A)
//    {
//        if (SetButtons(false, ControllerButton::ButtonA, m_pCommandsMap[ControllerButton::ButtonA].second))
//            executeCommand = true;
//    }
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_B)
//    {
//        if (SetButtons(false, ControllerButton::ButtonB, m_pCommandsMap[ControllerButton::ButtonB].second))
//            executeCommand = true;
//    }
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_X)
//    {
//        if (SetButtons(false, ControllerButton::ButtonX, m_pCommandsMap[ControllerButton::ButtonX].second))
//            executeCommand = true;
//    }
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_Y)
//    {
//        if (SetButtons(false, ControllerButton::ButtonY, m_pCommandsMap[ControllerButton::ButtonY].second))
//            executeCommand = true;
//    }
//    /* THUMBS */
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
//    {
//        m_CurrentButton = ControllerButton::ButtonRThumb;
//        std::cout << "ButtonRThumb pressed\n";
//    }
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
//    {
//        m_CurrentButton = ControllerButton::ButtonLThumb;
//        std::cout << "ButtonLThumb pressed\n";
//    }
//    /* SHOULDERS */
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
//    {
//        m_CurrentButton = ControllerButton::ButtonRShoulder;
//        executeCommand = true;
//    }
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
//    {
//        m_CurrentButton = ControllerButton::ButtonLShoulder;
//        executeCommand = true;
//    }
//    /* Arrows */
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
//    {
//        m_CurrentButton = ControllerButton::ButtonDown;
//        executeCommand = true;
//    }
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_UP)
//    {
//        m_CurrentButton = ControllerButton::ButtonUp;
//        executeCommand = true;
//    }
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
//    {
//        m_CurrentButton = ControllerButton::ButtonLeft;
//        executeCommand = true;
//    }
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
//    {
//        m_CurrentButton = ControllerButton::ButtonRight;
//        executeCommand = true;
//    }
//    /* GENERAL */
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_START)
//        ConfigureButtons();
//    else if (pGamePad->wButtons & XINPUT_GAMEPAD_BACK)
//    {
//        m_CurrentButton = ControllerButton::ButtonBack;
//        return false;
//    }
//    else
//    {
//        m_CurrentButton = ControllerButton::NoAction;
//        return true;
//    }
//
//    return true;
//}
#include  <typeinfo> 

Helheim::InputManager::InputManager()
{
	AddKeyToMap(ControllerButton::ButtonA, SDL_SCANCODE_A, ButtonPressType::BUTTON_HOLD, "DieCommand", new DieCommand(Helheim::Observer::OBSERVER_EVENTS::PLAYER_DIED_P1));
	AddKeyToMap(ControllerButton::ButtonB, SDL_SCANCODE_B, ButtonPressType::BUTTON_PRESSED, "ColorChangeCommand", new ColorChangeCommand(Helheim::Observer::OBSERVER_EVENTS::COLOR_CHANGE_P1));
	AddKeyToMap(ControllerButton::ButtonX, SDL_SCANCODE_X, ButtonPressType::BUTTON_RELEASED, "DieCommand", new DieCommand(Helheim::Observer::OBSERVER_EVENTS::PLAYER_DIED_P1));
	AddKeyToMap(ControllerButton::ButtonY, SDL_SCANCODE_Y, ButtonPressType::BUTTON_HOLD, "ColorChangeCommand", new ColorChangeCommand(Helheim::Observer::OBSERVER_EVENTS::COLOR_CHANGE_P1));
	AddKeyToMap(ControllerButton::ButtonStart, SDL_SCANCODE_ESCAPE, ButtonPressType::BUTTON_PRESSED, "ChangeButtonsCommand", new ChangeButtonsCommand());
}
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
	SDL_Scancode keyboardButton{ key.keyboardButton };

	SDL_Event event{};
	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.scancode == keyboardButton/* m_KeyboardKeysState[keyboardButton]*/)
			return true;
		if (WORD(controllerButton) & m_CurrentState.Gamepad.wButtons)
			return true;
	}
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
				std::cout << "Button - held down \n";
				executeCommand = true;
			}
		}
		else if (controllSecond.first.buttonState == ButtonPressType::BUTTON_PRESSED)
		{
			if (IsButtonPressed(controllSecond.first))
			{
				std::cout << "Button - pressed \n";
				executeCommand = true;
			}
		}
		else if (controllSecond.first.buttonState == ButtonPressType::BUTTON_RELEASED)
		{
			if (IsButtonReleased(controllSecond.first))
			{
				std::cout << "Button - released \n";
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
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
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