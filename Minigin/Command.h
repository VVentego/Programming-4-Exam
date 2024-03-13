#ifndef COMMAND
#define COMMAND
#include "Player.h"
class Player1ControllerComponent;
class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute(dae::Player1ControllerComponent* actor) = 0;
};
#endif // !COMMAND