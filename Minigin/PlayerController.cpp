#include "PlayerController.h"
#include "InputManager.h"

dae::PlayerController::PlayerController(GameObject* pOwner, const std::string& playerName, bool usingController) :
	Component(pOwner), m_PlayerName{ playerName }, m_UsingController{ usingController }
{
}

void dae::PlayerController::Update(const double deltaTime)
{
	m_deltaTime = deltaTime;

	HandleInput();
}

void dae::PlayerController::HandleInput()
{
	auto& input = InputManager::GetInstance();

	Command* command = m_UsingController ? input.ProcessXInput() : input.ProcessInput();

	if (command != nullptr)
	{
		command->Execute(this);
	}
}

void dae::PlayerController::Move(const float x, const float y)
{
	glm::vec3 currentPos = m_pOwner->GetLocalPosition();

	m_pOwner->SetLocalPosition(currentPos.x + m_MoveSpeed * x * static_cast<float>(m_deltaTime), 
		currentPos.y - m_MoveSpeed * y * static_cast<float>(m_deltaTime),
		0);
}

void dae::PlayerController::OnKillEnemy()
{
	Event increaseScoreEvent;
	increaseScoreEvent.type = EventType::SCORE_INCREASED;
	increaseScoreEvent.intValue = 50;
	increaseScoreEvent.stringValue = m_PlayerName.c_str();

	NotifyObservers(increaseScoreEvent);
}

void dae::PlayerController::OnPlayerDeath()
{
	Event playerDiedEvent;
	playerDiedEvent.type = EventType::PLAYER_DIED;
	playerDiedEvent.stringValue = m_PlayerName.c_str();

	NotifyObservers(playerDiedEvent);
}