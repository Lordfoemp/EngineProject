#pragma once
#include <Windows.h>
#include <XInput.h>

#include <vector>
#include <map>

#include "Command.h"

#include "Singleton.h"

#include <string>

#define GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define GAMEPAD_RIGHT_THUMB_DEADZONE 8689

namespace Helheim
{
	enum class ButtonPressType
	{
		BUTTON_HOLD,
		BUTTON_DOWN,
		BUTTON_UP
	};
	enum class ControllerButton
	{
		NoAction,

		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,

		ButtonDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonUp = XINPUT_GAMEPAD_DPAD_UP,
		ButtonLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonRight = XINPUT_GAMEPAD_DPAD_RIGHT,

		ButtonLThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		ButtonRThumb = XINPUT_GAMEPAD_RIGHT_THUMB,

		ButtonLShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		ButtonRShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,

		ButtonLTrigger,
		ButtonRTrigger,

		ButtonTrigger_DEADZONE = XINPUT_GAMEPAD_TRIGGER_THRESHOLD,

		ButtonLThumbStick_DEADZONE = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE,
		ButtonRThumbStick_DEADZONE = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE,

		ButtonLThumbStick,
		ButtonRThumbStick,

		ButtonBack = XINPUT_GAMEPAD_BACK,
		ButtonStart = XINPUT_GAMEPAD_START
	};

	class InputManager final/* : public Singleton<InputManager>*/
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;

	private:
		float m_PreviousButtonResetTime;
		float m_PreviousButtonCurrentTime;
		// -------------------------
		// LEFT STICK  | RIGHT STICK
		// -------------------------
		// [0]: X axis | [2]: X axis
		// [1]: Y axis | [3]: Y axis
		// -------------------------
		std::vector<float> m_ThumbStick_StartVals{};

		ControllerButton m_CurrentButton,
			m_PreviousButton,
			m_CurrentChangeButton,
			m_PreviousChangeButton;
		XINPUT_STATE m_ControllerState;
		XINPUT_VIBRATION m_Vibration;

		std::map<ControllerButton, std::pair<Helheim::Command*, ButtonPressType>> m_pCommandsMap;
		std::map<ControllerButton, std::string> m_pCommandNamesMap;

		void SetupButtonMap();
		void SetupButtonOutputMap();
		void PrintOutputs();

		bool ProcessKeyboard_MouseInputs();
		bool ProcessControllerInputs(const DWORD& dwResult);
		void ProcessTriggers(XINPUT_GAMEPAD* pGamePad);
		void ProcessThumbSticks(XINPUT_GAMEPAD* pGamePad, bool& executeCommand);
		bool ProcessButtons(XINPUT_GAMEPAD* pGamePad, bool& executeCommand);

		void ConfigureButtons();
		ControllerButton GetButtonChoice(bool& keepChecking);

		bool SetNewCurrenteButton(const bool changeButtons, ControllerButton& currButton, ControllerButton& prevButton, const ControllerButton& button, const ButtonPressType& buttonPressType)
		{
			currButton = button;

			if (buttonPressType == ButtonPressType::BUTTON_DOWN || buttonPressType == ButtonPressType::BUTTON_UP)
			{
				if (currButton != prevButton)
				{
					prevButton = currButton;

					if (changeButtons)
					{
						LOG_ENDLINE(m_pCommandNamesMap[button]);
					}

					return true;
				}

				return false;
			}
			else
			{
				currButton = button;
				prevButton = currButton;

				return true;
			}
		}
		bool SetButtons(const bool changeButtons, const ControllerButton& newButton, const ButtonPressType& buttonPressType)
		{
			if (changeButtons)
				return SetNewCurrenteButton(changeButtons, m_CurrentChangeButton, m_PreviousChangeButton, newButton, buttonPressType);
			else
				return SetNewCurrenteButton(changeButtons, m_CurrentButton, m_PreviousButton, newButton, buttonPressType);
		}

		void UpdateButtonForAction(const std::string& actionName, Helheim::Command* pCommand, bool& keepChecking, const ButtonPressType& buttonPressType);
	};
}