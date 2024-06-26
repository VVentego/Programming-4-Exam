#ifndef PLAYER
#define PLAYER
namespace dae
{
	class Command;
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
		virtual void HandleInput(Command*) = 0;
		virtual void MoveRight() = 0;
		virtual void MoveDown() = 0;
		virtual void MoveLeft() = 0;
		virtual void MoveUp() = 0;
		virtual void Shoot() = 0;
		virtual void Mute() = 0;
		virtual void Skip() = 0;
	};
}
#endif //PLAYER