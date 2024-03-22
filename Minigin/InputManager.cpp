#include "InputManager.h"
#include <SDL.h>
#include <imgui_impl_sdl2.h>
#include <Windows.h>
#include <XInput.h>
#include <thread>

dae::InputManager::InputManager() :
	m_InputImpl{ std::make_unique<InputManagerImpl>() }
{
	BindButtonMove(std::make_unique<Move>());

	BindXMovement(std::make_unique<Move>());

	BindAttack(std::make_unique<Attack>());
	BindXAttack(std::make_unique<Attack>());
	BindDeath(std::make_unique<KillPlayer>());
	BindXDeath(std::make_unique<KillPlayer>());
}

void dae::InputManager::BindXMovement(std::unique_ptr<Command> command)
{
	m_InputImpl->BindXMovement(std::move(command));
}

void dae::InputManager::BindButtonMove(std::unique_ptr<Command> command) 
{
	m_InputImpl->BindButtonMove(std::move(command)); 
}

void dae::InputManager::BindXAttack(std::unique_ptr<Command> command)
{
	m_InputImpl->BindXAttack(std::move(command));
}

void dae::InputManager::BindAttack(std::unique_ptr<Command> command)
{
	m_InputImpl->BindAttack(std::move(command));
}

void dae::InputManager::BindDeath(std::unique_ptr<Command> command)
{
	m_InputImpl->BindDeath(std::move(command));
}

void dae::InputManager::BindXDeath(std::unique_ptr<Command> command)
{
	m_InputImpl->BindXDeath(std::move(command));
}

dae::Command* dae::InputManager::ProcessInput()
{
	m_Quit = m_InputImpl->ShouldQuit();

	return m_InputImpl->DoProcessInput();
}

dae::Command* dae::InputManager::ProcessXInput()
{
	return m_InputImpl->DoProcessXInput();
}

dae::Command* dae::InputManager::InputManagerImpl::DoProcessXInput()
{
	m_Y = 0;
	m_X = 0;
	int controllerIndex{};
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


	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		m_Y = -1;
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		m_Y = 1;
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		m_X = -1;
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		m_X = 1;

	if (m_X != 0 or m_Y != 0)
	{
		m_XMove->Update(m_X, m_Y);
		return m_XMove.get();
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

	m_X = 0.0f;
	m_Y = 0.0f;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			m_ShouldQuit = true;
		}
		
		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.scancode)
			{
			case SDL_SCANCODE_C:
				return m_Death.get();
				break;
			case SDL_SCANCODE_X:
			case SDL_SCANCODE_Z: SDL_FALLTHROUGH;
				return m_Attack.get();
				break;
			}
		}

		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

			if (currentKeyStates[SDL_SCANCODE_S])
				m_Y = -1;
			if (currentKeyStates[SDL_SCANCODE_W])
				m_Y = 1;
			if (currentKeyStates[SDL_SCANCODE_A])
				m_X = -1;
			if (currentKeyStates[SDL_SCANCODE_D])
				m_X = 1;
		}
	}
	if (m_X != 0 or m_Y != 0)
	{
		m_Move->Update(m_X, m_Y);
		return m_Move.get();
	}
		//if (e.type == SDL_MOUSEBUTTONDOWN) {
		//}
		//ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
		return nullptr;
}