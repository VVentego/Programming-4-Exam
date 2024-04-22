#ifndef COMMAND
#define COMMAND
#include "Player.h"
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(dae::Player* actor) = 0;
	};
#endif // !COMMAND
}