#ifndef INPUTMANAGER
#define INPUTMANAGER

#include "Singleton.h"
#include <windows.h>
#include <XInput.h>
#include <iostream>
#include <thread>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
#endif // !INPUTMANAGER