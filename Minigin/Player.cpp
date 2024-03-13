#include "Player.h"

dae::Player::Player(GameObject* playerObject)
{
	m_pPlayerController1 = playerObject->GetComponent<Player1ControllerComponent>().get();
}

void dae::Player::MoveUp()
{
	if (m_pPlayerController1 != nullptr)
	{
		m_pPlayerController1->MoveUp();
	}

}void dae::Player::MoveRight()
{
	if (m_pPlayerController1 != nullptr)
	{
		m_pPlayerController1->MoveRight();
	}

}void dae::Player::MoveLeft()
{
	if (m_pPlayerController1 != nullptr)
	{
		m_pPlayerController1->MoveLeft();
	}

}void dae::Player::MoveDown()
{
	if (m_pPlayerController1 != nullptr)
	{
		m_pPlayerController1->MoveDown();
	}
}