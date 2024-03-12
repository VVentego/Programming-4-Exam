#include <SDL.h>
#include "InputManager.h"
#include <imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	//XINPUT_STATE currentState{};
	//int controllerIndex{};
	XINPUT_STATE currentState{};
	int controllerIndex{};

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}/*
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
		}
			*/
		
		ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
	}

	while (true)
	{
		auto t = std::chrono::high_resolution_clock::now();
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(controllerIndex, &currentState);
		std::cout << "\rsThumbLX: " << currentState.Gamepad.sThumbLX
			<< " - sThumbRX: " << currentState.Gamepad.sThumbRX;
		if (currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			break;
		auto t2 = std::chrono::high_resolution_clock::now() - t;
		t += std::chrono::milliseconds(16) - t2; // we want ~60 fps
		std::this_thread::sleep_until(t);
	}

	return true;
}
