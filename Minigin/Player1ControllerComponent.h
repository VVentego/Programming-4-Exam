#ifndef PLAYER1CONTROLLER
#define PLAYER1CONTROLLER
#include "Component.h"

namespace dae 
{
    class Player1ControllerComponent : 
        public Component
    {
    public:
        Player1ControllerComponent(GameObject* pOwner);
        virtual ~Player1ControllerComponent() = default;
        Player1ControllerComponent(const Player1ControllerComponent& other) = delete;
        Player1ControllerComponent(Player1ControllerComponent&& other) = delete;
        Player1ControllerComponent& operator=(const Player1ControllerComponent& other) = delete;
        Player1ControllerComponent& operator=(Player1ControllerComponent&& other) = delete;

        void MoveUp();
        void MoveRight();
        void MoveLeft();
        void MoveDown();

        void Update(const double deltaTime) override;
        void HandleInput();
    private:
        const float m_MoveSpeed{ 10.f };
        double m_deltaTime{};
    };
}
#endif //PLAYER1CONTROLLER