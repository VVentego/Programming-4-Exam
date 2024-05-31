#ifndef DIGDUGSTATE
#define DIGDUGSTATE
#include <LevelState.h>

class Scene;
class MainMenuState : public LevelState
{
public:
	MainMenuState();
	void OnEnter(dae::Scene& scene);
	void OnExit(dae::Scene& scene);
	void HandleEvent() override;

private:
	std::unique_ptr<GameObject> m_MainMenuObject;
};

class SinglePlayerState1 : public LevelState
{
public:
	SinglePlayerState1();
	void OnEnter(dae::Scene& scene);
	void OnExit(dae::Scene& scene);
	void HandleEvent();
private:

};
#endif // !DIGDUGSTATE

