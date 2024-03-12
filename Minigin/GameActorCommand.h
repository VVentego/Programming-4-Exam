#ifndef GAMEACTORCOMMAND
#define GAMEACTORCOMMAND
#include "Command.h"
#include "GameActor.h"

class GameActor;
class GameActorCommand :
    public Command
{
private:
    GameActor* m_pActor{};
protected:
    GameActor* GetGameActor() const { return m_pActor; }
    virtual void Execute() = 0;
public:
    GameActorCommand(GameActor* actor);
    virtual ~GameActorCommand() = default;
    GameActorCommand(const GameActorCommand& other) = delete;
    GameActorCommand(GameActorCommand&& other) = delete;
    GameActorCommand& operator=(const GameActorCommand& other) = delete;
    GameActorCommand& operator=(GameActorCommand&& other) = delete;
};

#ifndef MOVE
#define MOVE
class Move : 
    public GameActorCommand
{
    void Execute() override
    {
        //Implement this
        //GetGameActor()->Move(someValue);
    }
};
#endif // !MOVE
#endif // !GAMEACTORCOMMAND