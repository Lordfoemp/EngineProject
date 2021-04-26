#pragma once
#include <Windows.h>

#include <unordered_map>
#include <vector>
#include <string>
#include <XInput.h>


#include "InputHelper.h"

#define GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define GAMEPAD_RIGHT_THUMB_DEADZONE 8689

namespace Helheim
{
	//class InputManager final
	//{
	//	public:
	//		InputManager();
	//		~InputManager();
	//		bool ProcessInput(const float elapsedSec);
	//		bool IsPressed(ControllerButton button) const;
	//	private:
	//		float m_PreviousButtonResetTime;
	//		float m_PreviousButtonCurrentTime;
	//		// -------------------------
	//		// LEFT STICK  | RIGHT STICK
	//		// -------------------------
	//		// [0]: X axis | [2]: X axis
	//		// [1]: Y axis | [3]: Y axis
	//		// -------------------------
	//		std::vector<float> m_ThumbStick_StartVals{};
	//		ControllerButton m_CurrentButton,
	//			m_PreviousButton,
	//			m_CurrentChangeButton,
	//			m_PreviousChangeButton;
	//		XINPUT_STATE m_ControllerState;
	//		XINPUT_VIBRATION m_Vibration;
	//		std::map<ControllerButton, std::pair<Helheim::Command*, ButtonPressType>> m_pCommandsMap;
	//		std::map<ControllerButton, std::string> m_pCommandNamesMap;
	//		void SetupButtonMap();
	//		void SetupButtonOutputMap();
	//		void PrintOutputs();
	//		bool ProcessKeyboard_MouseInputs();
	//		bool ProcessControllerInputs(const DWORD& dwResult, const float elapsedSec);
	//		void ProcessTriggers(XINPUT_GAMEPAD* pGamePad);
	//		void ProcessThumbSticks(XINPUT_GAMEPAD* pGamePad, bool& executeCommand);
	//		bool ProcessButtons(XINPUT_GAMEPAD* pGamePad, bool& executeCommand);
	//		void ConfigureButtons();
	//		ControllerButton GetButtonChoice(bool& keepChecking);
	//		bool SetNewCurrenteButton(const bool changeButtons, ControllerButton& currButton, ControllerButton& prevButton, const ControllerButton& button, const ButtonPressType& buttonPressType)
	//		{
	//			currButton = button;
	//			if (buttonPressType == ButtonPressType::BUTTON_DOWN || buttonPressType == ButtonPressType::BUTTON_UP)
	//			{
	//				if (currButton != prevButton)
	//				{
	//					prevButton = currButton;
	//					if (changeButtons)
	//					{
	//						LOG_ENDLINE(m_pCommandNamesMap[button]);
	//					}
	//					return true;
	//				}
	//				return false;
	//			}
	//			else
	//			{
	//				currButton = button;
	//				prevButton = currButton;
	//				return true;
	//			}
	//		}
	//		bool SetButtons(const bool changeButtons, const ControllerButton& newButton, const ButtonPressType& buttonPressType)
	//		{
	//			if (changeButtons)
	//				return SetNewCurrenteButton(changeButtons, m_CurrentChangeButton, m_PreviousChangeButton, newButton, buttonPressType);
	//			else
	//				return SetNewCurrenteButton(changeButtons, m_CurrentButton, m_PreviousButton, newButton, buttonPressType);
	//		}
	//		void UpdateButtonForAction(const std::string& actionName, Helheim::Command* pCommand, bool& keepChecking, const ButtonPressType& buttonPressType);
	//};
	class Command;
	class InputManager final
	{
		public:
			InputManager();
			~InputManager();

			bool ProcessInput(const float elapsedSec);

			bool IsButtonPressed(const Key& key);
			bool IsButtonReleased(const Key& key);
			bool IsButtonDown(const Key& key);

			void EditKeyInMap();

		private:
			// Timer for the Old button reference
			float m_CurrentTimer_OldButton = 0.f;
			const float m_MaxTimer_OldButton = 0.5f;

			// Information about the controller/keyboard
			XINPUT_STATE m_CurrentState{};
			const Uint8* m_KeyboardKeysState{};

			// General
			ControllerButton m_Oldbutton = ControllerButton::NoAction;
			std::unordered_map<ControllerButton, std::pair<Key, Command*>> m_ControllerScheme;

			void ProcessAllControllerScheme();
			bool ProcessSDLInput();

			void UpdateOldButton(const float elapsedSec);

			void AddKeyToMap(const ControllerButton& cButton, const SDL_Scancode& kButton, const ButtonPressType& pressType, const std::string& name, Command* const pCommand);
			

			Command* GetCommand(const ControllerButton& cButton);
			Command* GetCommand(const SDL_Scancode& cButton);
	};
}