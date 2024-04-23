#include "InputManager.h"
#include <SDL.h>
#include <imgui_impl_sdl2.h>
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
		return m_XDeath.get();
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
	/*
	const bool invertY{ true };

	float LX = m_CurrentState.Gamepad.sThumbLX;
	float LY = invertY ? static_cast<float>(-m_CurrentState.Gamepad.sThumbLY) : static_cast<float>(m_CurrentState.Gamepad.sThumbLY);

	//determine how far the controller is pushed
	float magnitude = sqrt(LX * LX + LY * LY);

	//determine the direction the controller is pushed
	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}

	if (normalizedMagnitude != 0.0)
	{
		m_XMove->Update(normalizedLX * normalizedMagnitude * 2, -normalizedLY * normalizedMagnitude * 2);
		return m_XMove.get();
	}
	*/
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
				return m_Death.get();
				break;
			case SDL_SCANCODE_X:
			case SDL_SCANCODE_Z: SDL_FALLTHROUGH;
				return m_Attack.get();
				break;
			}
		}
		//if (e.type == SDL_MOUSEBUTTONDOWN) {
		//}
		//ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
	}
	return nullptr;
}