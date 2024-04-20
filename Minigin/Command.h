#ifndef COMMAND
#define COMMAND
#include "Player.h"
class DigDugController;
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(dae::DigDugController* actor) = 0;
	};
#endif // !COMMAND
}