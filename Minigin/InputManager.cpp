#include "InputManager.h"

dae::InputManager::InputManager() :
	m_InputImpl{ std::make_unique<InputManagerImpl>() }
{
	BindButtonMoveRight(std::make_unique<MoveRight>());
	BindButtonMoveDown(std::make_unique<MoveDown>());
	BindButtonMoveLeft(std::make_unique<MoveLeft>());
	BindButtonMoveUp(std::make_unique<MoveUp>());

	BindXButtonMoveRight(std::make_unique<MoveRight>());
	BindXButtonMoveDown(std::make_unique<MoveDown>());
	BindXButtonMoveLeft(std::make_unique<MoveLeft>());
	BindXButtonMoveUp(std::make_unique<MoveUp>());

	BindAttack(std::make_unique<Attack>());
	BindXAttack(std::make_unique<Attack>());
}

void dae::InputManager::BindXButtonMoveRight(std::unique_ptr<Command> command)
{
	m_InputImpl->BindXButtonMoveRight(std::move(command));
}

void dae::InputManager::BindXButtonMoveDown(std::unique_ptr<Command> command)
{
	m_InputImpl->BindXButtonMoveDown(std::move(command));
}

void dae::InputManager::BindXButtonMoveLeft(std::unique_ptr<Command> command)
{
	m_InputImpl->BindXButtonMoveLeft(std::move(command));
}

void dae::InputManager::BindXButtonMoveUp(std::unique_ptr<Command> command)
{
	m_InputImpl->BindButtonMoveUp(std::move(command));
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

void dae::InputManager::BindXAttack(std::unique_ptr<Command> command)
{
	m_InputImpl->BindXAttack(std::move(command));
}

void dae::InputManager::BindAttack(std::unique_ptr<Command> command)
{
	m_InputImpl->BindAttack(std::move(command));
}

void dae::InputManager::BindDeath(std::unique_ptr<Command> command)
{
	m_InputImpl->BindDeath(std::move(command));
}

void dae::InputManager::BindXDeath(std::unique_ptr<Command> command)
{
	m_InputImpl->BindXDeath(std::move(command));
}

dae::Command* dae::InputManager::ProcessInput()
{
	m_Quit = m_InputImpl->ShouldQuit();

	return m_InputImpl->DoProcessInput();
}

dae::Command* dae::InputManager::ProcessXInput(const int playerIdx)
{
	return m_InputImpl->DoProcessXInput(playerIdx);
}

