#ifndef INPUTMANAGER
#define INPUTMANAGER
#include "Singleton.h"
#include <vector>
#include  <memory>
#include "GameActorCommand.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		Command* ProcessInput();
		Command* ProcessXInput();

		bool HasQuit() const { return m_Quit; }

	private:
		
		class XInputManager;
		std::unique_ptr<XInputManager> m_XInputImpl;
		class SDLInputManager;
		std::unique_ptr<SDLInputManager> m_SDLInputImpl;

		bool m_Quit{ false };
	};


	class InputManager::XInputManager
	{
	public:

		XInputManager() = default;
		~XInputManager();
		XInputManager(const XInputManager& other) = delete;
		XInputManager(XInputManager&& other) = delete;
		XInputManager& operator=(const XInputManager& other) = delete;
		XInputManager& operator=(XInputManager&& other) = delete;

		Command* DoProcessInput();

		void BindMovement(Command* command) { m_Move = command; }

	private:
		Command* m_Move{};
	};

	class InputManager::SDLInputManager
	{
	public:

		SDLInputManager() = default;
		~SDLInputManager();
		SDLInputManager(const SDLInputManager& other) = delete;
		SDLInputManager(SDLInputManager&& other) = delete;
		SDLInputManager& operator=(const SDLInputManager& other) = delete;
		SDLInputManager& operator=(SDLInputManager&& other) = delete;

		Command* DoProcessInput();

		void BindButtonMove(Command* command) { m_Move = command; }

		bool ShouldQuit() const { return m_ShouldQuit; }

	private:
		Command* m_Move{};
		float m_X{};
		float m_Y{};

		bool m_ShouldQuit{ false };
	};
}
#endif // !INPUTMANAGER