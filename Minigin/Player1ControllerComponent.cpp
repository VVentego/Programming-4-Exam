#include "Player1ControllerComponent.h"
#include "InputManager.h"

dae::Player1ControllerComponent::Player1ControllerComponent(GameObject* pOwner) :
	Component(pOwner)
{
}

void dae::Player1ControllerComponent::Update(const double deltaTime)
{
	m_deltaTime = deltaTime;

	HandleInput();
}

void dae::Player1ControllerComponent::HandleInput()
{
	auto& input = InputManager::GetInstance();

	Command* command = input.ProcessInput();

	command->Execute(this);
}

void dae::Player1ControllerComponent::MoveUp()
{
	glm::vec3 currentPos = m_pOwner->GetLocalPosition();

	m_pOwner->SetLocalPosition(currentPos.x, currentPos.y + m_MoveSpeed * static_cast<float>(m_deltaTime), 0);
}

void dae::Player1ControllerComponent::MoveRight()
{
	glm::vec3 currentPos = m_pOwner->GetLocalPosition();

	m_pOwner->SetLocalPosition(currentPos.x + m_MoveSpeed * static_cast<float>(m_deltaTime), currentPos.y, 0);
}

void dae::Player1ControllerComponent::MoveLeft()
{
	glm::vec3 currentPos = m_pOwner->GetLocalPosition();

	m_pOwner->SetLocalPosition(currentPos.x - m_MoveSpeed * static_cast<float>(m_deltaTime), currentPos.y, 0);
}

void dae::Player1ControllerComponent::MoveDown()
{
	glm::vec3 currentPos = m_pOwner->GetLocalPosition();

	m_pOwner->SetLocalPosition(currentPos.x, currentPos.y - m_MoveSpeed * static_cast<float>(m_deltaTime), 0);
}