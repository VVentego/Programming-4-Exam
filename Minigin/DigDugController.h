#ifndef DIGDUG
#define DIGDUG

#include "Component.h"
#include "PumpBehaviorComponent.h"
namespace dae
{
    class TunnelManagerComponent;
    class DigDugController :
        public Component
    {
    public:
        DigDugController(GameObject* pOwner, const std::string& playerName, bool usingController, GameObject* pPump);
        virtual ~DigDugController() = default;
        DigDugController (const DigDugController& other) = delete;
        DigDugController(DigDugController&& other) = delete;
        DigDugController& operator=(const DigDugController& other) = delete;
        DigDugController& operator=(DigDugController&& other) = delete;

        void Update(const double deltaTime) override;
        void HandleInput();

        void MoveRight();
        void MoveDown();
        void MoveLeft();
        void MoveUp();
        void Shoot();
        void OnPlayerDeath();

        void SetTunnelManager(TunnelManagerComponent* pTunnelManager);

        const std::string m_PlayerName;
    private:
        const float m_MoveSpeed{ 20.f };
        float m_DistanceMoved{};
        const float m_MoveStepDistance{ 20.f };
        glm::vec2 m_Velocity{};
        bool m_UsingController{};
        Facing m_FacingDirection{ Facing::right };
        GameObject* m_pPumpObject{};
        PumpBehaviorComponent* m_Pump{};
        TunnelManagerComponent* m_pTunnelManager{};
    };
}
#endif // !DIGDUG
