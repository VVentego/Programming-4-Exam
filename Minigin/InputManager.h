#ifndef INPUTMANAGER
#define INPUTMANAGER
#include <vector>
#include <memory>
#include "InputSystem.h"
#include <Windows.h>
#include <Xinput.h>

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

		void AddPlayer1(Player& player1) override;
		void AddPlayer2(Player& player2) override;
		void RemovePlayer1() override;
		void RemovePlayer2() override;
		void BindButtonMoveRight(std::unique_ptr<Command> command);
		void BindButtonMoveDown(std::unique_ptr<Command> command);
		void BindButtonMoveLeft(std::unique_ptr<Command> command);
		void BindButtonMoveUp(std::unique_ptr<Command> command);
		void BindAttack(std::unique_ptr<Command> command);
		void BindMute(std::unique_ptr<Command> command);
		void BindSkip(std::unique_ptr<Command> command);

		void UpdateInput(const double deltaTime) override;
	private:
		class InputManagerImpl;
		std::unique_ptr<InputManagerImpl> m_InputImpl;
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

		void UpdateInput(const double);
		void AddPlayer1(Player& player1);
		void AddPlayer2(Player& player2);
		void RemovePlayer1();
		void RemovePlayer2();
		void BindButtonMoveLeft(std::unique_ptr<Command> command) { m_MoveLeft = std::move(command); }
		void BindButtonMoveDown(std::unique_ptr<Command> command) { m_MoveDown = std::move(command); }
		void BindButtonMoveRight(std::unique_ptr<Command> command) { m_MoveRight = std::move(command); }
		void BindButtonMoveUp(std::unique_ptr<Command> command) { m_MoveUp = std::move(command); }
		void BindAttack(std::unique_ptr<Command> command) { m_Attack = std::move(command); }
		void BindMute(std::unique_ptr<Command> command) { m_Mute = std::move(command); }
		void BindSkip(std::unique_ptr<Command> command) { m_Skip = std::move(command); }

		bool ShouldQuit() const { return m_ShouldQuit; }

	private:
		Command* DoProcessXInput(const int playerIdx);
		Command* DoProcessInput();

		void PollControllers();

		std::unique_ptr<Command> m_MoveRight{};
		std::unique_ptr<Command> m_MoveDown{};
		std::unique_ptr<Command> m_MoveLeft{};
		std::unique_ptr<Command> m_MoveUp{};
		std::unique_ptr<Command> m_Attack{};
		std::unique_ptr<Command> m_Mute{};
		std::unique_ptr<Command> m_Skip{};

		Player* m_pPlayer1{};
		Player* m_pPlayer2{};

		uint32_t m_NrControllers{ 0 };
		float m_PollTimer{ 2.f };
		const float m_TimeToPoll{ 2.f };
		bool m_ShouldQuit{ false };

		float m_X{};
		float m_Y{};
		XINPUT_STATE m_CurrentState0{};
		XINPUT_STATE m_PrevState0{};
		XINPUT_STATE m_CurrentState1{};
		XINPUT_STATE m_PrevState1{};
	};
}
#endif // !INPUTMANAGER