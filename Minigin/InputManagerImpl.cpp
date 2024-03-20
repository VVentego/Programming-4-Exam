#include "InputManagerImpl.h"
#include <SDL.h>
#include <imgui_impl_sdl2.h>
#include <Windows.h>
#include <XInput.h>
#include <thread>

dae::InputManagerImpl::~InputManagerImpl()
{
	//delete m_XMove;
	m_XMove = nullptr;

	//delete m_Move;
	m_Move = nullptr;
}

dae::Command* dae::InputManagerImpl::DoProcessXInput()
{
	XINPUT_STATE currentState{};
	int controllerIndex{};

	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(controllerIndex, &currentState);

	const bool invertY{ true };

	float LX = currentState.Gamepad.sThumbLX;
	float LY = invertY ? static_cast<float>(-currentState.Gamepad.sThumbLY) : static_cast<float>(currentState.Gamepad.sThumbLY);

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
		return m_XMove;
	}

	return nullptr;
}


dae::Command* dae::InputManagerImpl::DoProcessInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			m_ShouldQuit = true;
		}

		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_S)
				m_Y = -1;
			if (e.key.keysym.scancode == SDL_SCANCODE_W)
				m_Y = 1;
			if (e.key.keysym.scancode == SDL_SCANCODE_A)
				m_X = -1;
			if (e.key.keysym.scancode == SDL_SCANCODE_D)
				m_X = 1;
		}

		if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_S)
				m_Y = 0;
			if (e.key.keysym.scancode == SDL_SCANCODE_W)
				m_Y = 0;
			if (e.key.keysym.scancode == SDL_SCANCODE_A)
				m_X = 0;
			if (e.key.keysym.scancode == SDL_SCANCODE_D)
				m_X = 0;
		}

		if (m_X != 0 or m_Y != 0)
		{
			m_Move->Update(m_X, m_Y);
			return m_Move;
		}
	}
	//if (e.type == SDL_MOUSEBUTTONDOWN) {
	//}
	//ImGui_ImplSDL2_ProcessEvent(&e);
	// etc...
	return nullptr;
}
