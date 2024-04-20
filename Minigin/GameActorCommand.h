#ifndef GAMEACTORCOMMAND
#define GAMEACTORCOMMAND
#include "Command.h"

namespace dae
{
    class GameActorCommand :
        public Command
    {
    public:
        GameActorCommand() = default;
        virtual ~GameActorCommand() = default;
        virtual void Execute(DigDugController* actor) = 0;
    };

    class MoveRight :
        public GameActorCommand
    {
    public:
        void Execute(DigDugController* actor) override
        {
            actor->MoveRight();
        }
    };

    class MoveDown :
        public GameActorCommand
    {
    public:
        void Execute(DigDugController* actor) override
        {
            actor->MoveDown();
        }
    };

    class MoveLeft :
        public GameActorCommand
    {
    public:
        void Execute(DigDugController* actor) override
        {
            actor->MoveLeft();
        }
    };

    class MoveUp :
        public GameActorCommand
    {
    public:
        void Execute(DigDugController* actor) override
        {
            actor->MoveUp();
        }
    };
    class Attack :
        public GameActorCommand
    {
    public:
        void Execute(DigDugController* actor) override
        {
            actor->Shoot();
        }
    };

    class KillPlayer :
        public GameActorCommand
    {
    public:
        void Execute(DigDugController* actor) override
        {
            actor->OnPlayerDeath();
        }
    };
}
#endif // !GAMEACTORCOMMAND