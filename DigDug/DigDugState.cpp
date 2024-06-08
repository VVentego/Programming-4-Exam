#include "DigDugState.h"
#include "Enemy.h"
#include "RockBehavior.h"
#include "FygarBreathComponent.h"

using namespace dae;

DigDugState* DigDugNormalState::Update(DigDugController& digDug, const double deltaTime)
{
	if (digDug.m_InvulnerabilityTimer > 0)
	{
		digDug.m_InvulnerabilityTimer -= static_cast<float>(deltaTime);
	}

	if (digDug.m_NewFacingDirection != digDug.m_FacingDirection)
	{
		switch (digDug.m_NewFacingDirection)
		{
		case Facing::right:
			digDug.SetSpriteSheet(digDug.m_pWalkSpriteRight, 0.2);
			break;
		case Facing::down:
			digDug.SetSpriteSheet(digDug.m_pWalkSpriteDown, 0.2);
			break;
		case Facing::left:
			digDug.SetSpriteSheet(digDug.m_pWalkSpriteLeft, 0.2);
			break;
		case Facing::up:
			digDug.SetSpriteSheet(digDug.m_pWalkSpriteUp, 0.2);
			break;
		}
		digDug.m_FacingDirection = digDug.m_NewFacingDirection;
	}
	if (digDug.m_DistanceMoved < digDug.m_MoveStepDistance)
	{
		digDug.PlayMusic();
		glm::vec2 currentPos = digDug.m_pOwner->GetLocalPosition();

		digDug.m_pOwner->SetLocalPosition(currentPos.x + digDug.m_Velocity.x * static_cast<float>(deltaTime),
			currentPos.y + digDug.m_Velocity.y * static_cast<float>(deltaTime));

		digDug.m_DistanceMoved += digDug.m_MoveSpeed * static_cast<float>(deltaTime);
	}

	else
	{
		digDug.m_pOwner->SnapToGrid();
		digDug.StopMusic();
		digDug.m_Velocity = {};
	}

	if (m_Dead)
	{
		return new DigDugDeathState;
	}

	if (!digDug.InTunnel() || !digDug.CentreInTunnel())
	{
		return new DigDugDigState;
	}

	if (digDug.m_Pump->IsActive())
	{
		return new DigDugPumpState;
	}
	return nullptr;
}

void DigDugNormalState::OnEnter(DigDugController& digDug)
{
	switch (digDug.m_FacingDirection)
	{
	case Facing::right:
		digDug.SetSpriteSheet(digDug.m_pWalkSpriteRight, 0.2);
		break;
	case Facing::down:
		digDug.SetSpriteSheet(digDug.m_pWalkSpriteDown, 0.2);
		break;
	case Facing::left:
		digDug.SetSpriteSheet(digDug.m_pWalkSpriteLeft, 0.2);
		break;
	case Facing::up:
		digDug.SetSpriteSheet(digDug.m_pWalkSpriteUp, 0.2);
		break;
	}

	digDug.m_Pump->Reset();
}

void dae::DigDugNormalState::OnExit(DigDugController& digDug) 
{
	digDug.StopMusic();
}


void DigDugNormalState::HandleInput(DigDugController& digdug, Command* command) 
{
	if (digdug.m_DistanceMoved <= digdug.m_MoveStepDistance) return;
	if (command != nullptr)
	{
		command->Execute(&digdug);
	}
}

void dae::DigDugNormalState::HandleCollision(DigDugController& digDug, GameObject* other)
{ 
	if (other == nullptr or digDug.m_InvulnerabilityTimer > 0)
	{
		return;
	}
	if (auto enemy = other->GetComponent<Enemy>())
	{
		if (enemy->IsInflated() == true)
		{
			return;
		}
		m_Dead = true;
	}
	if (auto rock = other->GetComponent<RockBehavior>())
	{
		if (rock->CanKill() && !m_Dead)
		{
			m_Dead = true;
		}
	}
	if (auto fire = other->GetComponent<FygarBreathComponent>())
	{
		if (fire->IsActive())
		{
			m_Dead = true;
		}
	}
}

DigDugState* DigDugDeathState::Update(DigDugController& digDug, const double)
{
	if (digDug.IsDoneDying() && digDug.m_Lives > 0)
	{
		return new DigDugNormalState;
	}

	return nullptr;
}

void DigDugDeathState::OnEnter(DigDugController& digDug)
{
	ServiceLocator::GetSoundManager().Play(6, 100);
	digDug.RenderTunnel(false);
	digDug.m_Pump->Reset();

	digDug.SetSpriteSheet(digDug.m_pDeathSprite, 0.1);
}

void DigDugDeathState::OnExit(DigDugController& digDug)
{
	digDug.OnPlayerDeath();
	digDug.m_InvulnerabilityTimer = digDug.m_InvulnLength;
}

DigDugState* dae::DigDugDigState::Update(DigDugController& digDug, const double deltaTime)
{
	if (digDug.m_InvulnerabilityTimer > 0)
	{
		digDug.m_InvulnerabilityTimer -= static_cast<float>(deltaTime);
	}

	if (digDug.m_NewFacingDirection != digDug.m_FacingDirection)
	{
		switch (digDug.m_NewFacingDirection)
		{
		case Facing::right:
			digDug.SetSpriteSheet(digDug.m_pDigSpriteRight, 0.2);
			break;
		case Facing::down:
			digDug.SetSpriteSheet(digDug.m_pDigSpriteDown, 0.2);
			break;
		case Facing::left:
			digDug.SetSpriteSheet(digDug.m_pDigSpriteLeft, 0.2);
			break;
		case Facing::up:
			digDug.SetSpriteSheet(digDug.m_pDigSpriteUp, 0.2);
			break;
		}
		digDug.m_FacingDirection = digDug.m_NewFacingDirection;
	}
	if (digDug.m_DistanceMoved < digDug.m_MoveStepDistance)
	{
		digDug.PlayMusic();
		glm::vec2 currentPos = digDug.m_pOwner->GetLocalPosition();

		digDug.m_pOwner->SetLocalPosition(currentPos.x + digDug.m_Velocity.x * static_cast<float>(deltaTime),
			currentPos.y + digDug.m_Velocity.y * static_cast<float>(deltaTime));

		digDug.m_DistanceMoved += digDug.m_MoveSpeed * static_cast<float>(deltaTime);
	}

	if (digDug.m_DistanceMoved >= digDug.m_MoveStepDistance)
	{
		digDug.StopMusic();
		digDug.m_Velocity = {};
		digDug.m_pOwner->SnapToGrid();
		digDug.DigTunnel();
	}

	if (m_Dead)
	{
		return new DigDugDeathState;
	}

	if (digDug.m_Pump->IsActive())
	{
		return new DigDugPumpState;
	}

	if (digDug.InTunnel())
	{
		return new DigDugNormalState;
	}
	return nullptr;
}

void dae::DigDugDigState::OnEnter(DigDugController& digDug)
{
	digDug.RenderTunnel(true);
	digDug.m_Pump->Reset();

	switch (digDug.m_FacingDirection)
	{
	case Facing::right:
		digDug.SetSpriteSheet(digDug.m_pDigSpriteRight, 0.2);
		break;
	case Facing::down:
		digDug.SetSpriteSheet(digDug.m_pDigSpriteDown, 0.2);
		break;
	case Facing::left:
		digDug.SetSpriteSheet(digDug.m_pDigSpriteLeft, 0.2);
		break;
	case Facing::up:
		digDug.SetSpriteSheet(digDug.m_pDigSpriteUp, 0.2);
		break;
	}
}

void dae::DigDugDigState::OnExit(DigDugController& digDug) 
{
	digDug.RenderTunnel(false);

	digDug.StopMusic();
}

void dae::DigDugDigState::HandleInput(DigDugController& digDug, Command* command)
{
	if (digDug.m_DistanceMoved <= digDug.m_MoveStepDistance)
	{
		return;
	}
	if (command != nullptr)
	{
		command->Execute(&digDug);
	}
}

void dae::DigDugDigState::HandleCollision(DigDugController& digDug, GameObject* other)
{
	if (other == nullptr or digDug.m_InvulnerabilityTimer > 0)
	{
		return;
	}

	if (auto enemy = other->GetComponent<Enemy>())
	{
		if (enemy->IsInflated() == true)
		{
			return;
		}
		m_Dead = true;
	}
	if (auto rock = other->GetComponent<RockBehavior>())
	{
		if (rock->CanKill() && !m_Dead)
		{
			m_Dead = true;
		}
	}
	if (auto fire = other->GetComponent<FygarBreathComponent>())
	{
		if (fire->IsActive())
		{
			m_Dead = true;
		}
	}
}

DigDugState* dae::DigDugPumpState::Update(DigDugController& digDug, const double deltaTime)
{
	if (digDug.m_InvulnerabilityTimer > 0)
	{
		digDug.m_InvulnerabilityTimer -= static_cast<float>(deltaTime);
	}

	if (m_Dead)
	{
		return new DigDugDeathState;
	}

	if (digDug.m_DistanceMoved < digDug.m_MoveStepDistance || !digDug.m_Pump->IsActive())
	{
		return new DigDugNormalState;
	}

	return nullptr;
}

void dae::DigDugPumpState::OnEnter(DigDugController& digDug)
{
	switch (digDug.m_FacingDirection)
	{
	case Facing::right:
		digDug.SetSpriteSheet(digDug.m_pPumpSpriteRight, 0.2);
		break;
	case Facing::down:
		digDug.SetSpriteSheet(digDug.m_pPumpSpriteDown, 0.2);
		break;
	case Facing::left:
		digDug.SetSpriteSheet(digDug.m_pPumpSpriteLeft, 0.2);
		break;
	case Facing::up:
		digDug.SetSpriteSheet(digDug.m_pPumpSpriteUp, 0.2);
		break;
	}
}

void dae::DigDugPumpState::OnExit(DigDugController& digDug)
{
	digDug.m_Pump->Reset();
}

void dae::DigDugPumpState::HandleInput(DigDugController& digDug, Command* command)
{
	if (command != nullptr)
	{
		if (dynamic_cast<Attack*>(command) != nullptr)
		{
			auto currentTime = std::chrono::steady_clock::now();
			auto holdDuration = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_LastPressTime);
			if (holdDuration > m_ButtonTapThreshold)
			{
				// Button tapped
				command->Execute(&digDug);
			}
			else
			{
				//Attack every 0.3 seconds
				auto timeSinceAttack{ std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_LastAttackTime) };
				if (timeSinceAttack >= m_HoldButtonAttackInterval) 
				{
					command->Execute(&digDug);

					m_LastAttackTime = currentTime;
				}
			}
			m_LastPressTime = currentTime;
		}
		else
		{
			command->Execute(&digDug);
		}

	}
}

void dae::DigDugPumpState::HandleCollision(DigDugController& digDug, GameObject* other)
{
	if (other == nullptr or digDug.m_InvulnerabilityTimer > 0)
	{
		return;
	}
	if (auto enemy = other->GetComponent<Enemy>())
	{
		if (enemy->IsInflated() == true)
		{
			return;
		}
		m_Dead = true;
	}
	if (auto rock = other->GetComponent<RockBehavior>())
	{
		if (rock->CanKill() && !m_Dead)
		{
			m_Dead = true;
		}
	}
	if (auto fire = other->GetComponent<FygarBreathComponent>())
	{
		if (fire->IsActive())
		{
			m_Dead = true;
		}
	}
}
