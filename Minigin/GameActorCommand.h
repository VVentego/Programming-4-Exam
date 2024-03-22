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
        virtual void Execute(PlayerController* actor) = 0;
    };

    class Move :
        public GameActorCommand
    {
    public:
        void Execute(PlayerController* actor) override
        {
            actor->Move(m_InputX, m_InputY);
        }

        void Update(const float x, const float y) override
        {
            m_InputX = x;
            m_InputY = y;
        }

    private:
        float m_InputX{};
        float m_InputY{};
    };

    class Attack :
        public GameActorCommand
    {
    public:
        void Execute(PlayerController* actor) override
        {
            actor->OnKillEnemy();
        }
        void Update(const float, const float) override { return; }
    };

    class KillPlayer :
        public GameActorCommand
    {
    public:
        void Execute(PlayerController* actor) override
        {
            actor->OnPlayerDeath();
        }
        void Update(const float, const float) override { return; }
    };
}
#endif // !GAMEACTORCOMMAND