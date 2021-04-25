#pragma once
#include "SDL.h"

namespace Helheim
{
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
	enum class ButtonPressType
	{
		BUTTON_HOLD,
		BUTTON_PRESSED,
		BUTTON_RELEASED
	};
	struct Key
	{
		ControllerButton controllerButton = ControllerButton::NoAction;
		SDL_Scancode	 keyboardButton;
		ButtonPressType  buttonState;
		std::string		 commandName;
	};
}
