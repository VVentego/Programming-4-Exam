#ifndef DIGDUGSTATE
#define DIGDUGSTATE
#include "../Minigin/LevelState.h"

class MainMenuState : public LevelState
{
	MainMenuState();
	void OnEnter(Scene& scene);
	void OnExit(Scene& scene);
	void HandleEvent();

private:
	std::unique_ptr<GameObject> m_MainMenuObject;
};

class SinglePlayerState1 : public LevelState
{
	SinglePlayerState1();
	void OnEnter(Scene& scene);
	void OnExit(Scene& scene);
	void HandleEvent();
};
#endif // !DIGDUGSTATE

