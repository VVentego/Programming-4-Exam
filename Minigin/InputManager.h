#ifndef INPUTMANAGER
#define INPUTMANAGER
#include "Singleton.h"
#include <vector>
#include <memory>
#include "GameActorCommand.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		static InputManager& GetInstance() {
			static InputManager instance;
			return instance;
		}
		virtual ~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		Command* ProcessInput();
		Command* ProcessXInput();

		bool HasQuit() const { return m_Quit; }

	private:
		InputManager();
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

		Command* DoProcessXInput();
		Command* DoProcessInput();

		void BindXMovement(std::unique_ptr<Command> command) { m_XMove = std::move(command); }
		void BindButtonMove(std::unique_ptr<Command> command) { m_Move = std::move(command); }

		bool ShouldQuit() const { return m_ShouldQuit; }
	private:
		bool m_ShouldQuit{ false };

		std::unique_ptr<Command> m_XMove{};
		std::unique_ptr<Command> m_Move{};
		float m_X{};
		float m_Y{};
	};
}
#endif // !INPUTMANAGER