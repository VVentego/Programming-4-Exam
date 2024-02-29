#ifndef INPUTMANAGER
#define INPUTMANAGER

#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
#endif // !INPUTMANAGER