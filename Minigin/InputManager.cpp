#include <SDL.h>
#include "InputManager.h"
#include <../imgui/backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
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

	return true;
}
