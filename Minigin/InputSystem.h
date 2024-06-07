#ifndef INPUTSYSTEM
#define INPUTSYSTEM
#include "GameActorCommand.h"
#include <memory>
#include <SDL_events.h>

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
		virtual void BindAttack(std::unique_ptr<Command> command) = 0;
		virtual void BindSkip(std::unique_ptr<Command> command) = 0;

		virtual void UpdateInput(const double) = 0;
		virtual bool HasQuit() const { return m_Quit; }
		virtual void AddPlayer1(Player& player1) = 0;
		virtual void AddPlayer2(Player& player2) = 0;
		virtual void RemovePlayer1() = 0;
		virtual void RemovePlayer2() = 0;

	protected:
		bool m_Quit{ false };
	};

	class NullInputSystem : public InputSystem
	{
	public:
		NullInputSystem() = default;
		virtual ~NullInputSystem() = default;
		NullInputSystem(const NullInputSystem& other) = delete;
		NullInputSystem(NullInputSystem&& other) = delete;
		NullInputSystem& operator=(const NullInputSystem& other) = delete;
		NullInputSystem& operator=(NullInputSystem&& other) = delete;

		void BindButtonMoveRight(std::unique_ptr<Command>) override {};
		void BindButtonMoveDown(std::unique_ptr<Command>) override {};
		void BindButtonMoveLeft(std::unique_ptr<Command>) override {};
		void BindButtonMoveUp(std::unique_ptr<Command>) override {};
		void BindAttack(std::unique_ptr<Command>) override {};
		void BindSkip(std::unique_ptr<Command>) override {};

		virtual void UpdateInput(const double) 
		{
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT) {
					m_Quit = true;
				}
			}
		};
		void AddPlayer1(Player&) override {};
		void AddPlayer2(Player&) override {};
		void RemovePlayer1() override {};
		void RemovePlayer2() override {};
	private:
		bool HasQuit() const { return m_Quit; }
	};
}
#endif // !INPUTSYSTEM
