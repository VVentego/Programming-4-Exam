#ifndef FYGAR
#define FYGAR
#include <Component.h>
#include "Enemy.h"

namespace dae
{
	class FygarState;
	class SpriteAnimatorComponent;
	class SpriteSheet;
	class PumpBehaviorComponent;
	class FygarBreathComponent;
	class FygarBehavior : public Component, public Enemy
	{
	public:
		FygarBehavior(GameObject* pOwner, FygarBreathComponent* pFygarBreathComponent);
		~FygarBehavior();
		FygarBehavior(const FygarBehavior& other) = delete;
		FygarBehavior(FygarBehavior&& other) = delete;
		FygarBehavior& operator=(const FygarBehavior& other) = delete;
		FygarBehavior& operator=(FygarBehavior&& other) = delete;

		void Update(const double deltaTime) override;
		virtual void CollisionEvent(GameObject* other);

	protected:
		virtual void Die() override;
		virtual void ToggleFireBreath(const bool active);

		FygarBreathComponent* m_FygarBreathComponent{};
		std::shared_ptr<SpriteSheet> m_pWalkLeftSprite;
		std::shared_ptr<SpriteSheet> m_pWalkRightSprite;
		std::shared_ptr<SpriteSheet> m_pGhostSheet;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite1;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite2;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite3;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite4;
		std::shared_ptr<SpriteSheet> m_pFlattenedSprite;

		float m_FireTimer{};
		const float m_FireCooldown{ 5.f };
		const float m_FireRange{ 48.f };

	private:
		friend class FygarNormalState;
		friend class FygarGhostState;
		friend class FygarInflatedState;
		friend class FygarFlattenedState;
		friend class FygarFireBreathingState;
		bool PlayerInRange();
		virtual void CrushedByRock() override;
		FygarState* m_CurrentState;
	};
}
#endif // !FYGAR