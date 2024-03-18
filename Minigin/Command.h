#ifndef COMMAND
#define COMMAND
#include "Player.h"
class PlayerController;
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(dae::PlayerController* actor) = 0;
		virtual void Update(const float x, const float y) = 0;
	};
#endif // !COMMAND
}