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
	int m_Player1Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};

class SinglePlayerState2 : public LevelState
{
public:
	SinglePlayerState2() = default;
	~SinglePlayerState2() = default;
	SinglePlayerState2(const SinglePlayerState2& other) = delete;
	SinglePlayerState2(SinglePlayerState2&& other) = delete;
	SinglePlayerState2& operator=(const SinglePlayerState2& other) = delete;
	SinglePlayerState2& operator=(SinglePlayerState2&& other) = delete;

	void OnEnter(dae::Scene& scene);
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
	void HandleEvent(const Event& event) override;
private:
	int m_Player1Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};

class SinglePlayerState3 : public LevelState
{
public:
	SinglePlayerState3() = default;
	~SinglePlayerState3() = default;
	SinglePlayerState3(const SinglePlayerState3& other) = delete;
	SinglePlayerState3(SinglePlayerState3&& other) = delete;
	SinglePlayerState3& operator=(const SinglePlayerState3& other) = delete;
	SinglePlayerState3& operator=(SinglePlayerState3&& other) = delete;

	void OnEnter(dae::Scene& scene);
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
	void HandleEvent(const Event& event) override;
private:
	int m_Player1Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};

class CoopState1 : public LevelState
{
public:
	CoopState1() = default;
	~CoopState1() = default;
	CoopState1(const CoopState1& other) = delete;
	CoopState1(CoopState1&& other) = delete;
	CoopState1& operator=(const CoopState1& other) = delete;
	CoopState1& operator=(CoopState1&& other) = delete;

	void OnEnter(dae::Scene& scene);
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
	void HandleEvent(const Event& event) override;
private:
	int m_Player1Lives{ 3 };
	int m_Player2Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};

class CoopState2 : public LevelState
{
public:
	CoopState2() = default;
	~CoopState2() = default;
	CoopState2(const CoopState2& other) = delete;
	CoopState2(CoopState2&& other) = delete;
	CoopState2& operator=(const CoopState2& other) = delete;
	CoopState2& operator=(CoopState2&& other) = delete;

	void OnEnter(dae::Scene& scene);
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
	void HandleEvent(const Event& event) override;
private:
	int m_Player1Lives{ 3 };
	int m_Player2Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};

class CoopState3 : public LevelState
{
public:
	CoopState3() = default;
	~CoopState3() = default;
	CoopState3(const CoopState3& other) = delete;
	CoopState3(CoopState3&& other) = delete;
	CoopState3& operator=(const CoopState3& other) = delete;
	CoopState3& operator=(CoopState3&& other) = delete;

	void OnEnter(dae::Scene& scene);
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
	void HandleEvent(const Event& event) override;
private:
	int m_Player1Lives{ 3 };
	int m_Player2Lives{ 3 };
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
	int m_Player1Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};

class VersusPlayerState2 : public LevelState
{
public:
	VersusPlayerState2() = default;
	~VersusPlayerState2() = default;
	VersusPlayerState2(const VersusPlayerState2& other) = delete;
	VersusPlayerState2(VersusPlayerState2&& other) = delete;
	VersusPlayerState2& operator=(const VersusPlayerState2& other) = delete;
	VersusPlayerState2& operator=(VersusPlayerState2&& other) = delete;

	void OnEnter(dae::Scene& scene);
	void HandleEvent(const Event& event) override;
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
private:
	int m_Player1Lives{ 3 };
	float m_EndLevelDelay{ 1.f };
};

class VersusPlayerState3 : public LevelState
{
public:
	VersusPlayerState3() = default;
	~VersusPlayerState3() = default;
	VersusPlayerState3(const VersusPlayerState3& other) = delete;
	VersusPlayerState3(VersusPlayerState3&& other) = delete;
	VersusPlayerState3& operator=(const VersusPlayerState3& other) = delete;
	VersusPlayerState3& operator=(VersusPlayerState3&& other) = delete;

	void OnEnter(dae::Scene& scene);
	void HandleEvent(const Event& event) override;
	std::unique_ptr<LevelState> OnExit(dae::Scene& scene) override;
private:
	int m_Player1Lives{ 3 };
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

