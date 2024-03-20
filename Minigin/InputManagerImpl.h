#ifndef INPUTIMPL
#define INPUTIMPL
#include "GameActorCommand.h"

namespace dae
{
	class InputManagerImpl
	{
	public:
		InputManagerImpl() = default;
		~InputManagerImpl();
		InputManagerImpl(const InputManagerImpl& other) = delete;
		InputManagerImpl(InputManagerImpl&& other) = delete;
		InputManagerImpl& operator=(const InputManagerImpl& other) = delete;
		InputManagerImpl& operator=(InputManagerImpl&& other) = delete;

		Command* DoProcessXInput();
		Command* DoProcessInput();

		void BindXMovement(Command* command) { m_XMove = command; }
		void BindButtonMove(Command* command) { m_Move = command; }

		bool ShouldQuit() const { return m_ShouldQuit; }
	private:
		bool m_ShouldQuit{ false };

		Command* m_XMove{};
		Command* m_Move{};
		float m_X{};
		float m_Y{};
	};
}
#endif // !INPUTIMPL

