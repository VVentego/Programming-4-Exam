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
        virtual void Execute(Player* actor) = 0;
    };

    class MoveRight :
        public GameActorCommand
    {
    public:
        void Execute(Player* actor) override
        {
            actor->MoveRight();
        }
    };

    class MoveDown :
        public GameActorCommand
    {
    public:
        void Execute(Player* actor) override
        {
            actor->MoveDown();
        }
    };

    class MoveLeft :
        public GameActorCommand
    {
    public:
        void Execute(Player* actor) override
        {
            actor->MoveLeft();
        }
    };

    class MoveUp :
        public GameActorCommand
    {
    public:
        void Execute(Player* actor) override
        {
            actor->MoveUp();
        }
    };
    class Attack :
        public GameActorCommand
    {
    public:
        void Execute(Player* actor) override
        {
            actor->Shoot();
        }
    };
    class Mute :
        public GameActorCommand
    {
        void Execute(Player* actor) override
        {
            actor->Mute();
        }
    };
    class Skip :
        public GameActorCommand
    {
        void Execute(Player* actor) override
        {
            actor->Skip();
        }
    };
}
#endif // !GAMEACTORCOMMAND