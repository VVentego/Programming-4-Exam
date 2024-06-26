#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <Minigin.h>
#include <Scene.h>
#include <iostream>
#include <ServiceLocator.h>
#include "DigDugLevelState.h"

void LoadSounds(dae::SoundSystem& soundManager);

void load()
{
	//dae::SceneManager::GetInstance().CreateScene("Main");
	auto& soundManager = ServiceLocator::GetSoundManager();
	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color{ 0, 0, 0, 255 });
	dae::SceneManager::GetInstance().SetLevelState(std::make_unique<MainMenuState>());

	LoadSounds(soundManager);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}

void LoadSounds(dae::SoundSystem& soundManager)
{
	soundManager.AddTrack("pump_fire.wav", 0);
	soundManager.AddTrack("pump.wav", 1);
	soundManager.AddTrack("enemy_killed1.wav", 2);
	soundManager.AddTrack("enemy_pop.wav", 3);
	soundManager.AddTrack("life_lost.wav", 4);
	soundManager.AddTrack("Monster_Moving.mp3", 5);
	soundManager.AddTrack("enemy_touched.wav", 6);
	soundManager.AddTrack("Round_Clear_Music.mp3", 7);
	soundManager.AddTrack("result_screen_beep.wav", 8);
	soundManager.AddTrack("life_lost.wav", 9);
	soundManager.AddTrack("fygar_fire.wav", 10);

	soundManager.AddMusic("../Data/DigDug_Walking.mp3");
	soundManager.StopMusic();
}