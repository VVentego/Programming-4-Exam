#ifndef DIGDUGSTATE
#define DIGDUGSTATE
#include <LevelState.h>

class MainMenuState : public LevelState
{
public:
	MainMenuState();
	~MainMenuState();
	void OnEnter(dae::Scene& scene);
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
	void HandleEvent(const Event& event) override;

private:

};

class SinglePlayerState1 : public LevelState
{
public:
	SinglePlayerState1();
	~SinglePlayerState1();
	void OnEnter(dae::Scene& scene);
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
	void HandleEvent(const Event& event) override;
private:
	int m_Player0Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};
#endif // !DIGDUGSTATE

