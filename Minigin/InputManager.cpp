#include "InputManager.h"
#include <SDL.h>
#include <imgui_impl_sdl2.h>
#include <Windows.h>
#include <XInput.h>
#include <thread>

dae::InputManager::InputManager() :
	m_XInputImpl{ std::make_unique<XInputManager>() }
{
}

Command* dae::InputManager::ProcessInput()
{
	return m_SDLInputImpl->DoProcessInput();
	//return m_XInputImpl->DoProcessInput();
}

Command* dae::InputManager::XInputManager::DoProcessInput()
{
	XINPUT_STATE currentState{};
	int controllerIndex{};

	auto t = std::chrono::high_resolution_clock::now();
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(controllerIndex, &currentState);
	//std::cout << "\rsThumbLX: " << currentState.Gamepad.sThumbLX
	//	<< " - sThumbRX: " << currentState.Gamepad.sThumbRX;
	//if (currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		//break;
	auto t2 = std::chrono::high_resolution_clock::now() - t;
	t += std::chrono::milliseconds(16) - t2; // we want ~60 fps
	std::this_thread::sleep_until(t);

	return nullptr;
}

dae::InputManager::SDLInputManager::SDLInputManager()
{

}

Command* dae::InputManager::SDLInputManager::DoProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return nullptr;
		}
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.scancode)
			{
			case SDL_SCANCODE_W: SDL_FALLTHROUGH;
				return m_pButtonUp;
			case SDL_SCANCODE_A: SDL_FALLTHROUGH;
				return m_pButtonLeft;
			case SDL_SCANCODE_S: SDL_FALLTHROUGH;
				return m_pButtonDown;
			case SDL_SCANCODE_D:
				return m_pButtonRight;
			}
		}
		//if (e.type == SDL_MOUSEBUTTONDOWN) {
		//}
		//ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
	}
		return nullptr;
}
