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

		const bool CanKill() const { return m_CanKill; }
	private:
		friend class RockIdleState;
		friend class RockFallingState;
		friend class RockBreakState;
		void SetSprite(std::shared_ptr<SpriteSheet> spriteSheet);
		void Fall(const double deltaTime);
		bool IsInTunnel();
		void Die();
		bool IsDoneDying();

		const float m_FallSpeed{ 5.f };
		const float m_TunnelCheckOffset{ 2.f };
		RockState* m_CurrentState;
		SpriteAnimatorComponent* m_pAnimatorComponent{};
		std::shared_ptr<SpriteSheet> m_pNormalRockSprite;
		std::shared_ptr<SpriteSheet> m_pFallingRockSprite;
		std::shared_ptr<SpriteSheet> m_pBreakingRockSprite;
		bool m_CanKill{};
    };
}
#endif // !ROCK