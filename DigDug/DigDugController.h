#ifndef DIGDUG
#define DIGDUG

#include "../Minigin/Component.h"
#include "../Minigin/Player.h"
#include "PumpBehaviorComponent.h"

namespace dae
{
    struct ControllerInfo
    {
        bool usingController{ false };
        int playerControllerIdx{};
    };

    class TunnelManagerComponent;
    class DigDugController :
        public Component, public Player
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
        void OnPlayerDeath() override;
        virtual void CollisionEvent(GameObject* other) override;

        void SetTunnelManager(TunnelManagerComponent* pTunnelManager);

        const std::string m_PlayerName;
    private:
        const float m_MoveSpeed{ 20.f };
        float m_DistanceMoved{};
        const float m_MoveStepDistance{ 16.f };
        glm::vec2 m_Velocity{};
        ControllerInfo m_ControllerInfo{};
        Facing m_FacingDirection{ Facing::right };
        GameObject* m_pPumpObject{};
        PumpBehaviorComponent* m_Pump{};
        TunnelManagerComponent* m_pTunnelManager{};
    };
}
#endif // !DIGDUG
