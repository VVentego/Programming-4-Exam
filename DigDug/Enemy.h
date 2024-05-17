#ifndef ENEMY
#define ENEMY
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

	bool m_IsHooked{};
};
#endif // !ENEMY
