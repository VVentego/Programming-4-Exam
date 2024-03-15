#include "PlayerController.h"
#include "InputManager.h"

dae::PlayerController::PlayerController(GameObject* pOwner, bool usingController) :
	Component(pOwner), m_UsingController{ usingController }
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
