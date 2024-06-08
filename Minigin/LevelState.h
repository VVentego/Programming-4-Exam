#ifndef LEVELSTATE
#define LEVELSTATE
#include "Component.h"
#include <memory>

class LevelState : public EventListener
{
public:
	LevelState() = default;
	virtual ~LevelState() = default;
	virtual void OnEnter(dae::Scene& scene) = 0;
	virtual std::unique_ptr<LevelState> OnExit(dae::Scene& scene) = 0;
	virtual void HandleEvent(const Event& event) = 0;

	virtual bool IsExited() { return m_Exit; }
protected:
	int m_EnemiesLeft{};
	bool m_Exit{};
	std::unique_ptr<LevelState> m_NextState{};
};
#endif // !LEVELSTATE
