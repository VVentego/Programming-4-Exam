#ifndef PLAYER
#define PLAYER
#include "Player1ControllerComponent.h"

namespace dae 
{
    class Player1ControllerComponent;
    class Player
    {
    public:
        Player(GameObject* pPlayer);
        ~Player() = default;
        Player(const Player& other) = delete;
        Player(Player&& other) = delete;
        Player& operator=(const Player& other) = delete;
        Player& operator=(Player&& other) = delete;

        void SetPlayerController(Player1ControllerComponent* pPlayerController) { 
            m_pPlayerController1 = pPlayerController;
        }

        void MoveUp();
        void MoveRight();
        void MoveLeft();
        void MoveDown();
    private:
        Player1ControllerComponent* m_pPlayerController1{};
    };
}
#endif // !PLAYER
