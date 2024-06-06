#ifndef ENEMY
#define ENEMY
#include <memory>
#include <vector>
#include <GameObject.h>
#include <SpriteAnimatorComponent.h>

namespace dae
{
	class GameObject;
	class PumpBehaviorComponent;
	class Enemy
	{
	protected:
		Enemy(GameObject* m_pOwner);
		virtual ~Enemy() = default;
		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

		virtual void TrackPlayer();
		virtual void CheckForTunnel();
		virtual void FindNewDirection();
		virtual void SetSprite(std::shared_ptr<SpriteSheet> spriteSheet);
		virtual void SwapTarget(const double deltaTime);
		virtual void UpdateMovement();
		virtual void GhostSeek();
		virtual void SeekNearestTunnel();
		virtual bool IsInTunnel() const;
		virtual void CrushedByRock();
		virtual void GetFree();
		virtual void Die() = 0;

		bool m_IsHooked{};
		int m_InflationLevel{};
		const int m_MaxInflationLevel{ 3 };
		int m_AttackingPlayerIdx{};
		PumpBehaviorComponent* m_pPump{};
		bool m_Flattened{};
		std::vector<GameObject*> m_PlayersTransform{};
		SpriteAnimatorComponent* m_pAnimatorComponent{};

		Facing m_FacingDirection{ Facing::right };
		float m_Speed{ .1f };
		const float m_TimeToChangeTarget{ 10.f };
		float m_ChangeTargetTimer{};
		int m_TargetIdx{};
		float m_CheckDistance{ 5.f };

	public:
		virtual bool GetHooked() const { return m_IsHooked; }
		virtual void Inflate(const int playerIdx);
		virtual bool IsInflated() const { return m_InflationLevel > 0; }
		virtual const bool Flatten() const { return m_Flattened; }
		virtual void AddPlayerToChase(GameObject* playerTransform);
	private:
		GameObject* m_pEnemyOwner{};
	};
}
#endif // !ENEMY
