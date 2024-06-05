#ifndef ENEMY
#define ENEMY

namespace dae
{
	class PumpBehaviorComponent;
	class Enemy
	{
	protected:
		Enemy() = default;
		virtual ~Enemy() = default;
		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

	public:
		virtual bool GetHooked() const { return m_IsHooked; }
		virtual void Inflate(const int playerIdx) = 0;
		virtual bool IsInflated() const { return m_InflationLevel > 0; }
		virtual const bool Flatten() const { return m_Flattened; }
	protected:
		bool m_IsHooked{};
		int m_InflationLevel{};
		const int m_MaxInflationLevel{ 3 };
		int m_AttackingPlayerIdx{};
		PumpBehaviorComponent* m_pPump{};
		bool m_Flattened{};
	};
}
#endif // !ENEMY
