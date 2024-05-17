#ifndef POOKA
#define POOKA
#include "../Minigin/Component.h"
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

		void AddPlayerToChase(GameObject* playerTransform);
		void CollisionEvent(GameObject* other) override;

		bool GetHooked() const { return m_IsHooked; }
		void Inflate(const int playerIdx) override;
	private:
		friend class NormalState;
		friend class GhostState;
		friend class InflatedState;
		void TrackPlayer();
		void CheckForTunnel();
		void ReverseDirection();
		void SetSprite(std::shared_ptr<SpriteSheet> spriteSheet);
		void SwapTarget(const double deltaTime);
		void UpdateMovement();
		void SeekNearestTunnel();
		bool IsInTunnel() const;
		void Die();
		void GetFree();

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
		bool m_BumpedRecently{};
		PookaState* m_CurrentState;
		const int m_Size{ 14 };
		int m_AttackingPlayerIdx{};
		PumpBehaviorComponent* m_pPump{};
	};
}
#endif // !POOKA

