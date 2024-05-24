#include "InputManager.h"
#include <SDL.h>

dae::Command* dae::InputManager::InputManagerImpl::DoProcessXInput(const int playerIdx)
{
	m_Y = 0;
	m_X = 0;

	XINPUT_STATE* currentState{};
	XINPUT_STATE* prevState{};

	if (playerIdx == 0)
	{
		currentState = &m_CurrentState0;
		prevState = &m_PrevState0;
	}
	else if (playerIdx == 1)
	{
		currentState = &m_CurrentState1;
		prevState = &m_PrevState1;
	}
	else
	{
		return nullptr; // Invalid player index
	}

	*prevState = *currentState;

	// Retrieve the current state of the controller
	if (XInputGetState(playerIdx, currentState) != ERROR_SUCCESS)
	{
		return nullptr; // Controller is not connected or failed to retrieve state
	}
	if (!(prevState->Gamepad.wButtons & XINPUT_GAMEPAD_A) && (currentState->Gamepad.wButtons & XINPUT_GAMEPAD_A))
	{
		return m_Attack.get();
	}
	if (!(prevState->Gamepad.wButtons & XINPUT_GAMEPAD_B) && (currentState->Gamepad.wButtons & XINPUT_GAMEPAD_B))
	{
		return m_Attack.get();
	}

	if (!(prevState->Gamepad.wButtons & XINPUT_GAMEPAD_X) && (currentState->Gamepad.wButtons & XINPUT_GAMEPAD_X))
	{
	}

	if (currentState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		return m_MoveRight.get();
	}
	if (currentState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		return m_MoveDown.get();
	}
	if (currentState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		return m_MoveLeft.get();
	}
	if (currentState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		return m_MoveUp.get();
	}
	return nullptr;
}

dae::Command* dae::InputManager::InputManagerImpl::DoProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			m_ShouldQuit = true;
		}

		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.scancode)
			{
			case SDL_SCANCODE_D:
				return m_MoveRight.get();
				break;
			case SDL_SCANCODE_S:
				return m_MoveDown.get();
				break;
			case SDL_SCANCODE_A:
				return m_MoveLeft.get();
				break;
			case SDL_SCANCODE_W:
				return m_MoveUp.get();
				break;
			case SDL_SCANCODE_C:
				break;
			case SDL_SCANCODE_X:
			case SDL_SCANCODE_Z: SDL_FALLTHROUGH;
				return m_Attack.get();
				break;
			}
		}
	}
	return nullptr;
}

void dae::InputManager::InputManagerImpl::PollControllers()
{
	if (m_PollTimer > m_TimeToPoll)
	{
		m_NrControllers = 0;

		DWORD dwResult;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			// Simply get the state of the controller from XInput.
			dwResult = XInputGetState(i, &state);

			if (dwResult == ERROR_SUCCESS)
			{
				++m_NrControllers;
			}
		}
		m_PollTimer = 0;
	}
}

void dae::InputManager::InputManagerImpl::UpdateInput(const double deltaTime)
{
	m_PollTimer += static_cast<float>(deltaTime);
	//If there is no player 1, do nothing
	if (m_pPlayer1 == nullptr)
	{
		return;
	}

	//Singleplayer
	if (m_pPlayer2 == nullptr)
	{
		m_pPlayer1->HandleInput(DoProcessXInput(0));
		m_pPlayer1->HandleInput(DoProcessInput());
	}

	//Multiplayer
	else
	{
		//If there are two controllers, let the first player choose to use either controller or keyboard
		if (m_NrControllers >= 2)
		{
			m_pPlayer1->HandleInput(DoProcessXInput(0));
			m_pPlayer1->HandleInput(DoProcessInput());

			m_pPlayer2->HandleInput(DoProcessXInput(1));
		}
		//If there is only one controller, first player uses keyboard only
		else
		{
			m_pPlayer1->HandleInput(DoProcessInput());

			m_pPlayer2->HandleInput(DoProcessXInput(0));
		}
	}

	PollControllers();
}

void dae::InputManager::InputManagerImpl::AddPlayer1(Player& player1)
{
	m_pPlayer1 = &player1;
}

void dae::InputManager::InputManagerImpl::AddPlayer2(Player& player2)
{
	m_pPlayer2 = &player2;
}

void dae::InputManager::InputManagerImpl::RemovePlayer1()
{
	m_pPlayer1 = nullptr;
}

void dae::InputManager::InputManagerImpl::RemovePlayer2()
{
	m_pPlayer2 = nullptr;
}
