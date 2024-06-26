#ifndef POOKA
#define POOKA
#include <Component.h>
#include "Enemy.h"

namespace dae 
{
	class PookaState;
	class SpriteAnimatorComponent;
	class SpriteSheet;
	class PumpBehaviorComponent;

	class PookaBehavior final : public Component, public Enemy
	{
	public:
		PookaBehavior(GameObject* pOwner);
		~PookaBehavior();
		PookaBehavior(const PookaBehavior& other) = delete;
		PookaBehavior(PookaBehavior&& other) = delete;
		PookaBehavior& operator=(const PookaBehavior& other) = delete;
		PookaBehavior& operator=(PookaBehavior&& other) = delete;

		void Update(const double deltaTime) override;
		void CollisionEvent(GameObject* other) override;

	private:
		friend class PookaNormalState;
		friend class PookaGhostState;
		friend class PookaInflatedState;
		friend class PookaFlattenedState;
		void Die() override;
		void CrushedByRock() override;

		std::shared_ptr<SpriteSheet> m_pWalkLeftSprite;
		std::shared_ptr<SpriteSheet> m_pWalkRightSprite;
		std::shared_ptr<SpriteSheet> m_pGhostSheet;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite1;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite2;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite3;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite4;
		std::shared_ptr<SpriteSheet> m_pFlattenedSprite;

		Facing m_FacingDirection{ Facing::right };
		float m_Speed{ .1f };

		const float m_TimeToChangeTarget{ 10.f };
		float m_ChangeTargetTimer{};
		int m_TargetIdx{};
		std::vector<GameObject*> m_PlayersTransform;
		float m_CheckDistance{ 5.f };
		PookaState* m_CurrentState;
		const int m_Size{ 14 };
	};
}
#endif // !POOKA

