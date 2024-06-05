#ifndef FYGAR
#define FYGAR
#include <Component.h>
#include "Enemy.h"

namespace dae
{
	class SpriteAnimatorComponent;
	class SpriteSheet;
	class FygarState;
    class FygarBehavior :
        public Component, public Enemy
    {
		SpriteAnimatorComponent* m_pAnimatorComponent{};
		std::shared_ptr<SpriteSheet> m_pWalkSprite;
		std::shared_ptr<SpriteSheet> m_pGhostSheet;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite1;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite2;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite3;
		std::shared_ptr<SpriteSheet> m_pInflatedSprite4;

		Facing m_FacingDirection{ Facing::right };
		float m_Speed{ .1f };
		int m_InflationLevel{};
		const int m_MaxInflationLevel{ 3 };
		const float m_TimeToChangeTarget{ 10.f };
		float m_ChangeTargetTimer{};
		int m_TargetIdx{};
		std::vector<GameObject*> m_PlayersTransform;
		float m_CheckDistance{ 0.f };
		FygarState* m_CurrentState;
		const int m_Size{ 14 };
		int m_AttackingPlayerIdx{};
		PumpBehaviorComponent* m_pPump{};
    };
}
#endif // !FYGAR