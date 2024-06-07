#ifndef DIGDUGLEVELSTATE
#define DIGDUGLEVELSTATE
#include <LevelState.h>

class MainMenuState : public LevelState
{
public:
	MainMenuState() = default;
	~MainMenuState() = default;
	MainMenuState(const MainMenuState& other) = delete;
	MainMenuState(MainMenuState&& other) = delete;
	MainMenuState& operator=(const MainMenuState& other) = delete;
	MainMenuState& operator=(MainMenuState&& other) = delete;
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;

	void OnEnter(dae::Scene& scene);
	void HandleEvent(const Event& event) override;

private:

};

class SinglePlayerState1 : public LevelState
{
public:
	SinglePlayerState1() = default;
	~SinglePlayerState1() = default;
	SinglePlayerState1(const SinglePlayerState1& other) = delete;
	SinglePlayerState1(SinglePlayerState1&& other) = delete;
	SinglePlayerState1& operator=(const SinglePlayerState1& other) = delete;
	SinglePlayerState1& operator=(SinglePlayerState1&& other) = delete;

	void OnEnter(dae::Scene& scene);
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
	void HandleEvent(const Event& event) override;
private:
	int m_Player0Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};

class VersusPlayerState1 : public LevelState
{
public:
	VersusPlayerState1() = default;
	~VersusPlayerState1() = default;
	VersusPlayerState1(const VersusPlayerState1& other) = delete;
	VersusPlayerState1(VersusPlayerState1&& other) = delete;
	VersusPlayerState1& operator=(const VersusPlayerState1& other) = delete;
	VersusPlayerState1& operator=(VersusPlayerState1&& other) = delete;

	void OnEnter(dae::Scene& scene);
	void HandleEvent(const Event& event) override;
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
private:
	int m_Player0Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};

class HighScoreHandler;
class EndScreenState : public LevelState
{
public:
	EndScreenState() = default;
	~EndScreenState() = default;
	EndScreenState(const EndScreenState& other) = delete;
	EndScreenState(EndScreenState&& other) = delete;
	EndScreenState& operator=(const EndScreenState& other) = delete;
	EndScreenState& operator=(EndScreenState&& other) = delete;
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;

	void OnEnter(dae::Scene& scene);
	void HandleEvent(const Event& event) override;
};
#endif // !DIGDUGLEVELSTATE

