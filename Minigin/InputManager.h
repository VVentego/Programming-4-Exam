#ifndef INPUTMANAGER
#define INPUTMANAGER
#include <vector>
#include <memory>
#include "InputSystem.h"

namespace dae
{
	class InputManager final : public InputSystem
	{
	public:
		InputManager();
		virtual ~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		void BindButtonMoveRight(std::unique_ptr<Command> command);
		void BindButtonMoveDown(std::unique_ptr<Command> command);
		void BindButtonMoveLeft(std::unique_ptr<Command> command);
		void BindButtonMoveUp(std::unique_ptr<Command> command);
		void BindXButtonMoveRight(std::unique_ptr<Command> command);
		void BindXButtonMoveDown(std::unique_ptr<Command> command);
		void BindXButtonMoveLeft(std::unique_ptr<Command> command);
		void BindXButtonMoveUp(std::unique_ptr<Command> command);
		void BindXAttack(std::unique_ptr<Command> command);
		void BindAttack(std::unique_ptr<Command> command);

		Command* ProcessInput();
		Command* ProcessXInput(const int playerIdx);

		bool HasQuit() const { return m_Quit; }
		
	private:
		class InputManagerImpl;
		std::unique_ptr<InputManagerImpl> m_InputImpl;
		bool m_Quit{ false };
	};

	class InputManager::InputManagerImpl
	{
	public:
		InputManagerImpl() = default;
		~InputManagerImpl() = default;
		InputManagerImpl(const InputManagerImpl& other) = delete;
		InputManagerImpl(InputManagerImpl&& other) = delete;
		InputManagerImpl& operator=(const InputManagerImpl& other) = delete;
		InputManagerImpl& operator=(InputManagerImpl&& other) = delete;

		Command* DoProcessXInput(const int playerIdx);
		Command* DoProcessInput();
		void BindButtonMoveLeft(std::unique_ptr<Command> command) { m_MoveLeft = std::move(command); }
		void BindButtonMoveDown(std::unique_ptr<Command> command) { m_MoveDown = std::move(command); }
		void BindButtonMoveRight(std::unique_ptr<Command> command) { m_MoveRight = std::move(command); }
		void BindButtonMoveUp(std::unique_ptr<Command> command) { m_MoveUp = std::move(command); }
		void BindXButtonMoveRight(std::unique_ptr<Command> command) { m_XMoveRight = std::move(command); }
		void BindXButtonMoveDown(std::unique_ptr<Command> command) { m_XMoveDown = std::move(command); }
		void BindXButtonMoveLeft(std::unique_ptr<Command> command) { m_XMoveLeft = std::move(command); }
		void BindXButtonMoveUp(std::unique_ptr<Command> command) { m_XMoveUp = std::move(command); }
		void BindXAttack(std::unique_ptr<Command> command) { m_XAttack = std::move(command); }
		void BindAttack(std::unique_ptr<Command> command) { m_Attack = std::move(command); }

		bool ShouldQuit() const { return m_ShouldQuit; }
	private:
		std::unique_ptr<Command> m_XMoveRight{};
		std::unique_ptr<Command> m_XMoveDown{};
		std::unique_ptr<Command> m_XMoveLeft{};
		std::unique_ptr<Command> m_XMoveUp{};
		std::unique_ptr<Command> m_MoveRight{};
		std::unique_ptr<Command> m_MoveDown{};
		std::unique_ptr<Command> m_MoveLeft{};
		std::unique_ptr<Command> m_MoveUp{};
		std::unique_ptr<Command> m_XAttack{};
		std::unique_ptr<Command> m_Attack{};

		bool m_ShouldQuit{ false };

		float m_X{};
		float m_Y{};
	};
}
#endif // !INPUTMANAGER