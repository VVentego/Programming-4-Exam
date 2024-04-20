#include "DigDugController.h"
#include "InputManager.h"
#include "TunnelManagerComponent.h"

dae::DigDugController::DigDugController(GameObject* pOwner, const std::string& playerName, bool usingController, GameObject* pPump) :
	Component(pOwner), m_PlayerName{ playerName }, m_UsingController{ usingController }, m_pPumpObject{ pPump }
{
	assert(m_pPumpObject != nullptr);
	m_pPumpObject->SetParent(pOwner, false);

	m_Pump = m_pPumpObject->GetComponent<PumpBehaviorComponent>();
	assert(m_Pump != nullptr);

}

void dae::DigDugController::Update(const double deltaTime)
{
	HandleInput();

	if (m_DistanceMoved < m_MoveStepDistance)
	{
		glm::vec3 currentPos = m_pOwner->GetLocalPosition();

		m_pOwner->SetLocalPosition(currentPos.x + m_Velocity.x * static_cast<float>(deltaTime),
			currentPos.y + m_Velocity.y * static_cast<float>(deltaTime), 0);

		m_DistanceMoved += m_MoveSpeed * static_cast<float>(deltaTime);
	}

	else
	{
		m_Velocity = {};
	}
}

void dae::DigDugController::HandleInput()
{
	auto& input = InputManager::GetInstance();

	Command* command = m_UsingController ? input.ProcessXInput() : input.ProcessInput();

	if (command != nullptr)
	{
		if (m_DistanceMoved < m_MoveStepDistance) return;
		command->Execute(this);
	}
}

void dae::DigDugController::MoveRight()
{
	m_Velocity = { m_MoveSpeed, 0 };

	m_FacingDirection = Facing::right;
	m_DistanceMoved = 0;
}

void dae::DigDugController::MoveDown()
{
	m_Velocity = { 0, m_MoveSpeed };

	m_FacingDirection = Facing::down;
	m_DistanceMoved = 0;
}

void dae::DigDugController::MoveLeft()
{
	m_Velocity = { -m_MoveSpeed, 0 };

	m_FacingDirection = Facing::left;
	m_DistanceMoved = 0;
}

void dae::DigDugController::MoveUp()
{
	m_Velocity = { 0, -m_MoveSpeed };

	m_FacingDirection = Facing::up;
	m_DistanceMoved = 0;
}
void dae::DigDugController::Shoot()
{
	m_Pump->Fire(m_FacingDirection);
}

void dae::DigDugController::OnPlayerDeath()
{
	Event playerDiedEvent;
	playerDiedEvent.type = EventType::PLAYER_DIED;
	playerDiedEvent.stringValue = m_PlayerName.c_str();

	NotifyObservers(playerDiedEvent);
}

void dae::DigDugController::SetTunnelManager(TunnelManagerComponent* pTunnelManager)
{
	assert(pTunnelManager != nullptr);
	m_pTunnelManager = pTunnelManager;
}