#ifndef GAMEACTOR
#define GAMEACTOR

#include "GameObject.h"
#include "GameActorCommand.h"

class GameObject;
class GameActorCommand;
class GameActor
{
public:

	GameActor(GameObject* pControlledObject, std::unique_ptr<GameActorCommand> pActorCommand);
	virtual ~GameActor() = default;
	GameActor(const GameActor& other) = delete;
	GameActor(GameActor&& other) = delete;
	GameActor& operator=(const GameActor& other) = delete;
	GameActor& operator=(GameActor&& other) = delete;

private:
	GameObject* m_pPlayerObject;
	std::unique_ptr<GameActorCommand> m_pActorCommand;
};

#endif //!GAMEACTOR
