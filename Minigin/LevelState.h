#ifndef LEVELSTATE
#define LEVELSTATE
#include "Component.h"
using namespace dae;
class LevelState : public EventListener
{
public:
	LevelState();
	virtual ~LevelState() = default;
	virtual void OnEnter(Scene& scene) = 0;
	virtual void OnExit(Scene& scene) = 0;
	virtual void HandleEvent() = 0;

protected:
	GameObject* m_pPlayer1ScoreObject{};
	GameObject* m_pPlayer2ScoreObject{};
	GameObject* m_pPlayer1LivesObject{};
	GameObject* m_pPlayer2LivesObject{};

	int m_EnemiesLeft{};
};
#endif // !LEVELSTATE
