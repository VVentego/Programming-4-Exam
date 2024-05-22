#ifndef DIGDUG
#define DIGDUG

#include <Component.h>
#include <Player.h>
#include "PumpBehaviorComponent.h"

namespace dae
{
    class TunnelManagerComponent;
    class DigDugState;
    class DigDugController final :
        public Component, public Player, public EventListener
    {
    public:
        DigDugController(GameObject* pOwner, const std::string& playerName, ControllerInfo controllerInfo, GameObject* pPump);
        virtual ~DigDugController() = default;
        DigDugController (const DigDugController& other) = delete;
        DigDugController(DigDugController&& other) = delete;
        DigDugController& operator=(const DigDugController& other) = delete;
        DigDugController& operator=(DigDugController&& other) = delete;

        void Update(const double deltaTime) override;
        void HandleInput();

        void MoveRight() override;
        void MoveDown() override;
        void MoveLeft() override;
        void MoveUp() override;
        void Shoot() override;
        virtual void CollisionEvent(GameObject* other) override;

        void SetTunnelManager(TunnelManagerComponent* pTunnelManager);

        void HandleEvent(const Event& event);

        const std::string m_PlayerName;
    private:
        friend class NormalState;
        friend class DigState;
        const float m_MoveSpeed{ 20.f };
        float m_DistanceMoved{};
        const float m_MoveStepDistance{ 16.f };
        glm::vec2 m_Velocity{};
        ControllerInfo m_ControllerInfo{};
        Facing m_FacingDirection{ Facing::right };
        GameObject* m_pPumpObject{};
        PumpBehaviorComponent* m_Pump{};
        TunnelManagerComponent* m_pTunnelManager{};
        DigDugState* m_CurrentState{};

        std::queue<Command*>* m_CommandQueue{};
    };
}
#endif // !DIGDUG
