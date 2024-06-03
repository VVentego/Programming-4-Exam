#ifndef DIGDUG
#define DIGDUG
#include <Component.h>
#include <Player.h>
#include "PumpBehaviorComponent.h"

namespace dae
{
    class TunnelManagerComponent;
    class DigDugState;
    class SpriteAnimatorComponent;
    class SpriteSheet;
    class DigDugController final :
        public Component, public Player, public EventListener
    {
    public:
        DigDugController(GameObject* pOwner, const std::string& playerName, GameObject* pPump);
        ~DigDugController();
        DigDugController (const DigDugController& other) = delete;
        DigDugController(DigDugController&& other) = delete;
        DigDugController& operator=(const DigDugController& other) = delete;
        DigDugController& operator=(DigDugController&& other) = delete;

        void Update(const double deltaTime) override;
        void HandleInput(Command* command) override;

        void MoveRight() override;
        void MoveDown() override;
        void MoveLeft() override;
        void MoveUp() override;
        void Shoot() override;
        void OnPlayerDeath();
        virtual void CollisionEvent(GameObject* other) override;

        void SetTunnelManager(TunnelManagerComponent* pTunnelManager);
        void SetStartPos(const glm::vec2 pos) { m_StartPos = pos; }
        void HandleEvent(const Event& event);

        const std::string m_PlayerName;
    private:
        friend class DigDugNormalState;
        friend class DigDugDigState;
        friend class DigDugDeathState;
        void SetSpriteSheet(std::shared_ptr<SpriteSheet> spriteSheet, const double frameTime);
        void DigTunnel();
        bool InTunnel();
        bool IsDoneDying();
        void PlayMusic();
        void StopMusic();
        void RenderTunnel(const bool doRender);
        const float m_MoveSpeed{ 20.f };
        const float m_CheckDistance{ 3.f };
        float m_DistanceMoved{};
        const float m_MoveStepDistance{ 16.f };
        glm::vec2 m_Velocity{};
        Facing m_NewFacingDirection{};
        Facing m_FacingDirection{ Facing::right };
        GameObject* m_pPumpObject{};
        SpriteAnimatorComponent* m_pAnimatorComponent{};
        PumpBehaviorComponent* m_Pump{};
        TunnelManagerComponent* m_pTunnelManager{};
        glm::vec2 m_Size{};
        glm::vec2 m_StartPos{};
        DigDugState* m_CurrentState;
        std::shared_ptr<SpriteSheet> m_pWalkSpriteRight;
        std::shared_ptr<SpriteSheet> m_pWalkSpriteDown;
        std::shared_ptr<SpriteSheet> m_pWalkSpriteLeft;
        std::shared_ptr<SpriteSheet> m_pWalkSpriteUp;
        std::shared_ptr<SpriteSheet> m_pDigSpriteRight;
        std::shared_ptr<SpriteSheet> m_pDigSpriteDown;
        std::shared_ptr<SpriteSheet> m_pDigSpriteLeft;
        std::shared_ptr<SpriteSheet> m_pDigSpriteUp;
        std::shared_ptr<SpriteSheet> m_pDeathSprite;
        TextureComponent* m_pTunnelTexture{};

        int m_Lives{ 3 };
    };
}
#endif // !DIGDUG
