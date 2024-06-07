#pragma once
#include "FygarBehavior.h"

namespace dae
{
    class FygarPlayerState;
	class FygarPlayerController final : public FygarBehavior,
		public Player
	{
    public:
        FygarPlayerController(GameObject* pOwner, FygarBreathComponent* breath);
        ~FygarPlayerController();
        FygarPlayerController(const FygarPlayerController& other) = delete;
        FygarPlayerController(FygarPlayerController&& other) = delete;
        FygarPlayerController& operator=(const FygarPlayerController& other) = delete;
        FygarPlayerController& operator=(FygarPlayerController&& other) = delete;

        void Update(const double deltaTime) override;
        void HandleInput(Command* command) override;

        void MoveRight() override;
        void MoveDown() override;
        void MoveLeft() override;
        void MoveUp() override;
        void Shoot() override;
        void Mute() override;
        void Skip() override;

        void SetStartPos(const glm::vec2 pos) { m_StartPos = pos; }

    private:
        friend class FygarPlayerNormalState;
        friend class FygarPlayerGhostState;
        friend class FygarPlayerInflatedState;
        friend class FygarPlayerFlattenedState;
        friend class FygarPlayerFireBreathingState;

        void CrushedByRock() override;
        void Die() override;
        void Respawn();
        const float m_MoveSpeed{ 40.f };
        const float m_CheckDistance{ 3.f };
        const float m_MoveStepDistance{ 16.f };
        Facing m_NewFacingDirection{};
        Facing m_FacingDirection{ Facing::right };
        float m_DistanceMoved{ m_MoveStepDistance + 1 };
        const float m_InvulnLength{ 2.f };
        float m_InvulnerabilityTimer{ m_InvulnLength };
        glm::vec2 m_Velocity{};
        glm::vec2 m_StartPos{};
        FygarPlayerState* m_CurrentState;
        const std::string m_PlayerName{ "Player1" };
        int m_Lives{ 3 };
        bool m_BreatheFire{};
        bool m_Dead{};
    };
}
