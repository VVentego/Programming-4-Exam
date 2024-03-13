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
		Command* ProcessInput();
		void AddPlayer(Player* pPlayer) { m_pPlayers.emplace_back(pPlayer); }
	private:
		std::vector<Player*> m_pPlayers;
		
		class XInputManager;
		std::unique_ptr<XInputManager> m_XInputImpl;
		class SDLInputManager;
		std::unique_ptr<SDLInputManager> m_SDLInputImpl;
	};


	class InputManager::XInputManager
	{
	public:

		XInputManager() = default;
		~XInputManager() = default;
		XInputManager(const XInputManager& other) = delete;
		XInputManager(XInputManager&& other) = delete;
		XInputManager& operator=(const XInputManager& other) = delete;
		XInputManager& operator=(XInputManager&& other) = delete;
		std::vector<Player*> m_pPlayers;

		Command* DoProcessInput();
		void AddPlayer(Player* pPlayer) { m_pPlayers.emplace_back(pPlayer); }

		//void BindButtonUp(Command* command) {};
		//void BindButtonDown(Command* command) {};
		//void BindButtonLeft(Command* command) {};
		//void BindButtonRight(Command* command) {};

	private:
		Command* m_pButtonUp{};
		Command* m_pButtonDown{};
		Command* m_pButtonLeft{};
		Command* m_pButtonRight{};
	};

	class InputManager::SDLInputManager
	{
	public:

		SDLInputManager();
		~SDLInputManager() = default;
		SDLInputManager(const SDLInputManager& other) = delete;
		SDLInputManager(SDLInputManager&& other) = delete;
		SDLInputManager& operator=(const SDLInputManager& other) = delete;
		SDLInputManager& operator=(SDLInputManager&& other) = delete;
		std::vector<Player*> m_pPlayers;

		Command* DoProcessInput();
		void AddPlayer(Player* pPlayer) { m_pPlayers.emplace_back(pPlayer); }

		void BindButtonUp(Command* command) { m_pButtonUp = command; }
		void BindButtonDown(Command* command) { m_pButtonUp = command; }
		void BindButtonLeft(Command* command) { m_pButtonUp = command; }
		void BindButtonRight(Command* command) { m_pButtonUp = command; }

	private:
		Command* m_pButtonUp;
		Command* m_pButtonDown;
		Command* m_pButtonLeft;
		Command* m_pButtonRight;
	};
}
#endif // !INPUTMANAGER