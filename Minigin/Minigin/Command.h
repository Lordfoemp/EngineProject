#pragma once
#include <Windows.h>
#include <XInput.h>
#include <iostream>

#define LOG(x) std::cout << x;
#define LOG_ENDLINE(x) std::cout << x << '\n';

#include "GameObject.h"
//#include "HealthComponent.h"
#include "LevelComponent.h"
//#include "../MiniGame/JumpComponent.h"

//#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Locator.h"
#include "Audio.h"

#include "../MiniGame/QBERT.h"

namespace Helheim
{	
	class Command
	{
		public:
			virtual ~Command() = default;
			virtual void Execute() = 0;

		protected:

	};
	
	// X/Y/A/B commands
	class EscapeCommand : public Command
	{
		public:
			EscapeCommand(QBERT* pQBERT, GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp)
				: m_pQbert{ pQBERT }
				, m_pLevelGO{ pLevelGO }
				, m_JumpUp{ jumpUp }
				, m_JumpLeft{ jumpLeft }
			{}

			void Execute() override { Escape(); };

		private:
			bool m_JumpUp;
			bool m_JumpLeft;
			QBERT* m_pQbert;
			GameObject* m_pLevelGO;
			void Escape()
			{
				// Disable all texture and enable the right one with the finding of a cube
				m_pQbert->ResetAllSprites();
				// Set the correct sprite when jumping
				m_pQbert->SetJumpingSprite(m_JumpLeft, m_JumpUp);
				m_pQbert->Escape(m_JumpLeft, m_JumpUp);
			}
	};
	class DieCommand : public Command
	{
		public:
			DieCommand(const Helheim::Observer::OBSERVER_EVENTS& event)
			: m_Event(event)
			{}
			void Execute() override { Die(); };

		private:
			Helheim::Observer::OBSERVER_EVENTS m_Event;
			void Die() 
			{ 
				LOG_ENDLINE("Deaded - ");

				//LoggingAudio* pLoggingAudio{ dynamic_cast<LoggingAudio*>(Helheim::Locator::GetAudioService()) };
				//if (pLoggingAudio)
				//	pLoggingAudio->RequestPlaySound(AudioMessages::PLAYER_DIED);
				//else
				//	dynamic_cast<ConsoleAudio*>(Helheim::Locator::GetAudioService())->RequestPlaySound(AudioMessages::PLAYER_DIED);

				//auto scene{ Locator::GetSceneService()->GetActiveScene() };
				//auto object{ scene->GetObjectByName("QBERT - P1") };
				////object->GetComponent<Helheim::HealthComponent>()->Die(m_Event);
			}
	};
	class ColorChangeCommand : public Command
	{
		public:
			ColorChangeCommand(const Helheim::Observer::OBSERVER_EVENTS& event)
			: m_Event(event)
			{}
			void Execute() override { ChangeColor(); };

		private:
			Helheim::Observer::OBSERVER_EVENTS m_Event;
			void ChangeColor()
			{
				LOG_ENDLINE("Color changed - ");

				LoggingAudio* pLoggingAudio{ dynamic_cast<LoggingAudio*>(Helheim::Locator::GetAudioService()) };
				if (pLoggingAudio)
					pLoggingAudio->RequestPlaySound(AudioMessages::SCORE_UP);
				else
					dynamic_cast<ConsoleAudio*>(Helheim::Locator::GetAudioService())->RequestPlaySound(AudioMessages::SCORE_UP);

				//auto scene{ Helheim::SceneManager::GetInstance().GetActiveScene() };
				auto scene{ Locator::GetSceneService()->GetActiveScene() };
				auto object{ scene->GetObjectByName("LevelCube") };
				object->GetComponent<Helheim::LevelComponent>()->ColorChange(m_Event);
			}
	};

	/*class JumpCommand : public Command
	{
		public:
			void Execute() override { Jump(); };

		private:
			void Jump() { LOG_ENDLINE("Jump - "); }
	};*/
	class FireCommand : public Command
	{
		public:
			void Execute() override { Fire(); };

		private:
			void Fire() { LOG_ENDLINE("Fire - "); }
	};
	class DuckCommand : public Command
	{
		public:
			void Execute() override { Duck(); };

		private:
			void Duck() { LOG_ENDLINE("Duck - "); }
	};
	class FartCommand : public Command
	{
		public:
			void Execute() override { Fart(); };
		
		private:
			void Fart() { LOG_ENDLINE("Fart - "); }
	};
	
	// Thumb stick commands
	class MoveCommand : public Command
	{
		struct Direction_Move
		{
			float direction_X;
			float direction_Y;
		};
		public:
			void Execute() override { Move(); };
			void SetDirection(const Direction_Move& dir) { m_Movement = dir; };

		private:
			Direction_Move m_Movement;

			void Move() 
			{ 
				std::string output{ "Move - " };
				if (m_Movement.direction_X > 0)
					output += " RIGHT &";
				else
					output += " LEFT &";
				if (m_Movement.direction_Y > 0)
					output += " FORWARD";
				else
					output += " BACK";

				LOG_ENDLINE(output);
			}
	};
	class AimCommand : public Command
	{
		struct Direction_Aim
		{
			float direction_X;
			float direction_Y;
		};
		public:
			void Execute() override { Aim(); };			
			void SetDirection(const Direction_Aim& dir) { m_Movement = dir; };

		private:
			Direction_Aim m_Movement;

			void Aim() 
			{ 
				std::string output{ "Aim - " };
				if (m_Movement.direction_X > 0)
					output += " RIGHT &";
				else
					output += " LEFT &";
				if (m_Movement.direction_Y > 0)
					output += " UP";
				else
					output += " DOWN";

				LOG_ENDLINE(output);
			}
	};

	// Trigger commands
	class DriveCommand : public Command
	{
		public:
			DriveCommand(const std::string& dir)
				: m_Direction{ dir }
			{}

			void Execute() override { Drive(); };

		private:
			std::string m_Direction;
			void Drive() 
			{ 
				std::string output{ "Driving " + m_Direction + " - " };
				LOG_ENDLINE(output); 
			}
	};

	// Shoulder commands
	class ScopeCommand : public Command
	{
		public:
			void Execute() override { Scope(); };

		private:
			void Scope() { LOG_ENDLINE("Scope - "); }
	};
	class ShootCommand : public Command
	{
		public:
			void Execute() override { Shoot(); };

		private:
			void Shoot() { LOG_ENDLINE("Shoot - "); }
	};

	// Arrow commands
	class JumpCommand : public Command
	{
		public:
			JumpCommand(QBERT* pQBERT, GameObject* pLevelGO, const bool jumpLeft, const bool jumpUp)
				: m_pQbert{ pQBERT }
				, m_pLevelGO{ pLevelGO }
				, m_JumpUp{ jumpUp }
				, m_JumpLeft{ jumpLeft }
			{}

			void Execute() override { Jump(); };

		private:
			bool m_JumpUp;
			bool m_JumpLeft;
			QBERT* m_pQbert;
			GameObject* m_pLevelGO;
			void Jump()
			{
				// Disable all texture and enable the right one with the finding of a cube
				m_pQbert->ResetAllSprites();
				// Set the correct sprite when jumping
				m_pQbert->SetJumpingSprite(m_JumpLeft, m_JumpUp);
				if (m_pQbert->Jump(m_JumpLeft, m_JumpUp))
					m_pQbert->Score();
			}
	};
	
	class ScrollInventoryCommand : public Command
	{
		public:
			ScrollInventoryCommand(const bool scrollLEFT, const bool scrollRIGHT, const bool scrollUP, const bool scrollDOWN)
				: m_ScrollLEFT{ scrollLEFT }
				, m_ScrollRIGHT{ scrollRIGHT }
				, m_ScrollUP{ scrollUP }
				, m_ScrollDOWN{ scrollDOWN }
			{}

			void Execute() override { ScrollInventory(); };

		private:
			bool m_ScrollLEFT, 
				 m_ScrollRIGHT,
				 m_ScrollUP,
				 m_ScrollDOWN;
			void ScrollInventory()
			{
				std::string output{ "Scrolling " };
				if (m_ScrollLEFT)
					output += "LEFT \n";
				else if(m_ScrollRIGHT)
					output += "RIGHT \n";
				if (m_ScrollUP)
					output += "UP \n";
				else if (m_ScrollDOWN)
					output += "DOWN \n";

				LOG_ENDLINE(output);
			}
	};

	// Change buttons commands
	class ChangeButtonsCommand : public Command
	{
		public:
			void Execute() override { ChangeButtons(); };

		private:
			void ChangeButtons()
			{ 
				LOG_ENDLINE("Changeeee - "); 
				//Locator::GetInputService()->EditKeyInMap();
			}
	};

	// No command
	class NULLCommand : public Command
	{
		public:
			void Execute() override {};
			
		private:
	};
}