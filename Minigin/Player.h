#ifndef PLAYER
#define PLAYER
namespace dae
{
	class Player
	{
	protected:
		Player() = default;
		virtual ~Player() = default;
		Player(const Player&) = delete;
		Player(Player&&) = delete;
		Player& operator=(const Player&) = delete;
		Player& operator=(Player&&) = delete;

	public:
		virtual void MoveRight() = 0;
		virtual void MoveDown() = 0;
		virtual void MoveLeft() = 0;
		virtual void MoveUp() = 0;
		virtual void Shoot() = 0;
		virtual void OnPlayerDeath() = 0;
	};
}
#endif //PLAYER