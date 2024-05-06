#ifndef POOKA
#define POOKA
#include "../Minigin/Component.h"

namespace dae 
{
	class PookaState;
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

		void AddPlayerToChase(const Transform* playerTransform);
		void CollisionEvent(GameObject* other) override;

		void TrackPlayer();
	private:
		Facing m_FacingDirection{ Facing::right };
		int m_InflationLevel{};
		const int m_MaxInflationLevel{ 3 };
		const float m_TimeToChangeTarget{ 10.f };
		float m_ChangeTargetTimer{};
		int m_TargetIdx{};
		std::vector<const Transform*> m_PlayersTransform;
		bool m_BumpedRecently{};
		PookaState* m_CurrentState;
	};
}
#endif // !POOKA

