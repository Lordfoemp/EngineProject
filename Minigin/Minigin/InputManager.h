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
			void AddKeyToMap(const ControllerButton& cButton, const SDL_Scancode& kButton, const ButtonPressType& pressType, const std::string& name, Command* const pCommand);

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

			Command* GetCommand(const ControllerButton& cButton);
			Command* GetCommand(const SDL_Scancode& cButton);
	};
}