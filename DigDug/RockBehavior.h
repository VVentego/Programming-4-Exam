#ifndef ROCK
#define ROCK
#include <Component.h>
#include <SpriteAnimatorComponent.h>

namespace dae
{
	class SpriteAnimatorComponent;
	class SpriteSheet;
	class RockState;
	class RockBehavior :
        public Component
    {
	public:
		RockBehavior(GameObject* pOwner);
		~RockBehavior();
		RockBehavior(const RockBehavior& other) = delete;
		RockBehavior(RockBehavior&& other) = delete;
		RockBehavior& operator=(const RockBehavior& other) = delete;
		RockBehavior& operator=(RockBehavior&& other) = delete;

		void Update(const double deltaTime) override;
		void AddPlayer(GameObject* player);

		const bool CanKill() const { return m_CanKill; }
		void CollisionEvent(GameObject* other) override;
		const std::string& GetInstigatingPlayer() const;
	private:
		friend class RockIdleState;
		friend class RockFallingState;
		friend class RockBreakState;
		void SetSprite(std::shared_ptr<SpriteSheet> spriteSheet);
		void Fall(const double deltaTime);
		const bool IsInTunnel() const;
		const bool DeepCheckInTunnel() const;
		void Die();
		bool IsDoneDying();
		GameObject* GetNearestPlayer();
		void SetInstigatingPlayer();
		const float m_FallSpeed{ 10.f };
		const float m_TunnelCheckOffset{ 10.f };
		RockState* m_CurrentState;
		SpriteAnimatorComponent* m_pAnimatorComponent{};
		std::vector<GameObject*> m_pPlayers{};
		std::shared_ptr<SpriteSheet> m_pNormalRockSprite;
		std::shared_ptr<SpriteSheet> m_pFallingRockSprite;
		std::shared_ptr<SpriteSheet> m_pBreakingRockSprite;
		bool m_CanKill{};
		int m_KillCount{};
		std::string m_InstigatingPlayerName{};
    };
}
#endif // !ROCK