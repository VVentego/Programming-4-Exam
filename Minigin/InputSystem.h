#ifndef INPUTSYSTEM
#define INPUTSYSTEM
#include "GameActorCommand.h"

namespace dae
{
	class InputSystem
	{
	public:
		InputSystem() = default;
		virtual ~InputSystem() = default;
		InputSystem(const InputSystem& other) = delete;
		InputSystem(InputSystem&& other) = delete;
		InputSystem& operator=(const InputSystem& other) = delete;
		InputSystem& operator=(InputSystem&& other) = delete;

		virtual void BindButtonMoveRight(std::unique_ptr<Command> command) = 0;
		virtual void BindButtonMoveDown(std::unique_ptr<Command> command) = 0;
		virtual void BindButtonMoveLeft(std::unique_ptr<Command> command) = 0;
		virtual void BindButtonMoveUp(std::unique_ptr<Command> command) = 0;
		virtual void BindXButtonMoveRight(std::unique_ptr<Command> command) = 0;
		virtual void BindXButtonMoveDown(std::unique_ptr<Command> command) = 0;
		virtual void BindXButtonMoveLeft(std::unique_ptr<Command> command) = 0;
		virtual void BindXButtonMoveUp(std::unique_ptr<Command> command) = 0;
		virtual void BindXAttack(std::unique_ptr<Command> command) = 0;
		virtual void BindAttack(std::unique_ptr<Command> command) = 0;
		virtual void BindDeath(std::unique_ptr<Command> command) = 0;
		virtual void BindXDeath(std::unique_ptr<Command> command) = 0;

		virtual Command* ProcessInput() = 0;
		virtual Command* ProcessXInput(const int playerIdx) = 0;

		virtual bool HasQuit() const { return m_Quit; }

	protected:
		bool m_Quit{ false };
	};
}
#endif // !INPUTSYSTEM
