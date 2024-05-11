#ifndef POOKA
#define POOKA
#include "../Minigin/Component.h"

namespace dae 
{
	class PookaState;
	class SpriteAnimatorComponent;
	class SpriteSheet;

	class PookaBehavior final : public Component
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

		void TrackPlayer();
	private:
		friend class NormalState;
		friend class GhostState;
		void CheckForTunnel();
		void ReverseDirection();
		void SetSprite(std::shared_ptr<SpriteSheet> spriteSheet);

		SpriteAnimatorComponent* m_pAnimatorComponent{};
		std::shared_ptr<SpriteSheet> m_pWalkSprite;
		std::shared_ptr<SpriteSheet> m_pGhostSheet;

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
	};
}
#endif // !POOKA

