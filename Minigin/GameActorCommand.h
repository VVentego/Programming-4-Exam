#ifndef GAMEACTORCOMMAND
#define GAMEACTORCOMMAND
#include "Command.h"

namespace dae
{
    class GameActorCommand :
        public Command
    {
    public:
        GameActorCommand() {};
        virtual ~GameActorCommand() = default;
        virtual void Execute(Player1ControllerComponent* actor) = 0;
    };

    class MoveUp :
        public GameActorCommand
    {
        void Execute(Player1ControllerComponent* actor) override
        {
            actor->MoveUp();
        }
    };
    
    class MoveDown :
        public GameActorCommand
    {
        void Execute(Player1ControllerComponent* actor) override
        {
            actor->MoveDown();
        }
    }; 
   
    class MoveLeft :
        public GameActorCommand
    {
        void Execute(Player1ControllerComponent* actor) override
        {
            actor->MoveLeft();
        }
    }; 
    
    class MoveRight :
        public GameActorCommand
    {
        void Execute(Player1ControllerComponent* actor) override
        {
            actor->MoveRight();
        }
    };
}
#endif // !GAMEACTORCOMMAND