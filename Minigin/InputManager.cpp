#include "InputManager.h"

dae::InputManager::InputManager() :
	m_InputImpl{ std::make_unique<InputManagerImpl>() }
{
	BindButtonMoveRight(std::make_unique<MoveRight>());
	BindButtonMoveDown(std::make_unique<MoveDown>());
	BindButtonMoveLeft(std::make_unique<MoveLeft>());
	BindButtonMoveUp(std::make_unique<MoveUp>());
	BindAttack(std::make_unique<Attack>());
	BindMute(std::make_unique<Mute>());
	BindSkip(std::make_unique<Skip>());
}

void dae::InputManager::AddPlayer1(Player& player1)
{
	m_InputImpl->AddPlayer1(player1);
}

void dae::InputManager::AddPlayer2(Player& player2)
{
	m_InputImpl->AddPlayer2(player2);
}

void dae::InputManager::RemovePlayer1()
{
	m_InputImpl->RemovePlayer1();
}

void dae::InputManager::RemovePlayer2()
{
	m_InputImpl->RemovePlayer2();
}

void dae::InputManager::BindButtonMoveRight(std::unique_ptr<Command> command)
{
	m_InputImpl->BindButtonMoveRight(std::move(command));
}

void dae::InputManager::BindButtonMoveDown(std::unique_ptr<Command> command)
{
	m_InputImpl->BindButtonMoveDown(std::move(command));
}

void dae::InputManager::BindButtonMoveLeft(std::unique_ptr<Command> command)
{
	m_InputImpl->BindButtonMoveLeft(std::move(command));
}

void dae::InputManager::BindButtonMoveUp(std::unique_ptr<Command> command)
{
	m_InputImpl->BindButtonMoveUp(std::move(command));
}

void dae::InputManager::BindAttack(std::unique_ptr<Command> command)
{
	m_InputImpl->BindAttack(std::move(command));
}

void dae::InputManager::BindMute(std::unique_ptr<Command> command)
{
	m_InputImpl->BindMute(std::move(command));
}

void dae::InputManager::BindSkip(std::unique_ptr<Command> command)
{
	m_InputImpl->BindSkip(std::move(command));
}

void dae::InputManager::UpdateInput(const double deltaTime)
{
	m_InputImpl->UpdateInput(deltaTime);
	m_Quit = m_InputImpl->ShouldQuit();
}
