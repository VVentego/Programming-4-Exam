#include "InputManager.h"
#include <SDL.h>
#include <Windows.h>
#include <XInput.h>

dae::Command* dae::InputManager::InputManagerImpl::DoProcessXInput(const int playerIdx)
{
	m_Y = 0;
	m_X = 0;
	int controllerIndex{ playerIdx };
	static XINPUT_STATE m_CurrentState;
	static XINPUT_STATE m_PrevState;

	m_PrevState = m_CurrentState;
	XInputGetState(controllerIndex, &m_CurrentState);

	if (!(m_PrevState.Gamepad.wButtons & XINPUT_GAMEPAD_A) && (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A))
	{
		return m_XAttack.get();
	}
	if (!(m_PrevState.Gamepad.wButtons & XINPUT_GAMEPAD_B) && (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B))
	{
		return m_XAttack.get();
	}

	if (!(m_PrevState.Gamepad.wButtons & XINPUT_GAMEPAD_X) && (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X))
	{
	}


	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		return m_XMoveRight.get();
	}
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		return m_XMoveDown.get();
	}
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		return m_XMoveLeft.get();
	}
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	{
		return m_XMoveUp.get();
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