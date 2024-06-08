#include "FygarPlayerState.h"

using namespace dae;
FygarPlayerState* dae::FygarPlayerNormalState::Update(FygarPlayerController& fygar, const double deltaTime)
{
	if (fygar.m_NewFacingDirection != fygar.m_FacingDirection)
	{
		switch (fygar.m_NewFacingDirection)
		{
		case Facing::right:
			fygar.SetSprite(fygar.m_pWalkRightSprite);
			break;
		case Facing::down:
			fygar.SetSprite(fygar.m_pWalkLeftSprite);
			break;
		case Facing::left:
			fygar.SetSprite(fygar.m_pWalkLeftSprite);
			break;
		case Facing::up:
			fygar.SetSprite(fygar.m_pWalkRightSprite);
			break;
		}
		fygar.m_FacingDirection = fygar.m_NewFacingDirection;
	}
	if (fygar.m_DistanceMoved < fygar.m_MoveStepDistance)
	{
		glm::vec2 currentPos = fygar.m_pOwner->GetLocalPosition();

		fygar.m_pOwner->SetLocalPosition(currentPos.x + fygar.m_Velocity.x * static_cast<float>(deltaTime),
			currentPos.y + fygar.m_Velocity.y * static_cast<float>(deltaTime));

		fygar.m_DistanceMoved += fygar.m_MoveSpeed * static_cast<float>(deltaTime);
	}

	else
	{
		fygar.m_pOwner->SnapToGrid();
		fygar.m_Velocity = {};
	}

	if (fygar.m_InflationLevel > 0 || fygar.m_IsHooked)
	{
		return new FygarPlayerInflatedState;
	}

	if (!fygar.IsInTunnel())
	{
		return new FygarPlayerGhostState;
	}

	if (fygar.m_BreatheFire)
	{
		return new FygarPlayerFireBreathingState;
	}
	return nullptr;
}

void dae::FygarPlayerNormalState::OnEnter(FygarPlayerController& fygar)
{
	switch (fygar.m_FacingDirection)
	{
	case Facing::right:
		fygar.SetSprite(fygar.m_pWalkRightSprite);
		break;
	case Facing::down:
		fygar.SetSprite(fygar.m_pWalkLeftSprite);
		break;
	case Facing::left:
		fygar.SetSprite(fygar.m_pWalkLeftSprite);
		break;
	case Facing::up:
		fygar.SetSprite(fygar.m_pWalkRightSprite);
		break;
	}
}

void dae::FygarPlayerNormalState::OnExit(FygarPlayerController&)
{
}

void dae::FygarPlayerNormalState::HandleInput(FygarPlayerController& fygar, Command* command)
{
	if (fygar.m_DistanceMoved <= fygar.m_MoveStepDistance) return;
	if (command != nullptr)
	{
		command->Execute(&fygar);
	}
}

FygarPlayerState* dae::FygarPlayerGhostState::Update(FygarPlayerController& fygar, const double deltaTime)
{
	if (fygar.m_DistanceMoved < fygar.m_MoveStepDistance)
	{
		glm::vec2 currentPos = fygar.m_pOwner->GetLocalPosition();

		fygar.m_pOwner->SetLocalPosition(currentPos.x + fygar.m_Velocity.x * static_cast<float>(deltaTime),
			currentPos.y + fygar.m_Velocity.y * static_cast<float>(deltaTime));

		fygar.m_DistanceMoved += fygar.m_GhostSpeed * static_cast<float>(deltaTime);
	}

	else
	{
		fygar.m_pOwner->SnapToGrid();
		fygar.m_Velocity = {};
	}

	if (fygar.IsInTunnel())
	{
		return new FygarPlayerNormalState;
	}

	if (fygar.m_Flattened == true)
	{
		return new FygarPlayerFlattenedState;
	}

	if (fygar.m_InflationLevel > 0 || fygar.m_IsHooked)
	{
		return new FygarPlayerInflatedState;
	}

    return nullptr;
}

void dae::FygarPlayerGhostState::OnEnter(FygarPlayerController& fygar)
{
	fygar.SetSprite(fygar.m_pGhostSheet);
	ServiceLocator::GetSoundManager().Play(5, 100);
}

void dae::FygarPlayerGhostState::OnExit(FygarPlayerController&)
{
}

void dae::FygarPlayerGhostState::HandleInput(FygarPlayerController& fygar, Command* command)
{
	if (fygar.m_DistanceMoved <= fygar.m_MoveStepDistance) return;
	if (command != nullptr)
	{
		if (dynamic_cast<Attack*>(command))
		{
			return;
		}
		command->Execute(&fygar);
	}
}

FygarPlayerState* dae::FygarPlayerInflatedState::Update(FygarPlayerController& fygar, const double deltaTime)
{
	if (fygar.m_FireTimer < fygar.m_FireCooldown)
	{
		fygar.m_FireTimer += static_cast<float>(deltaTime);
	}
	m_DeflationTimer += static_cast<float>(deltaTime);

	if (m_DeflationTimer > m_TimeToDeflate)
	{
		if (fygar.m_InflationLevel <= 0)
		{
			return new FygarPlayerNormalState;
		}
		--fygar.m_InflationLevel;
	}

	if (fygar.m_Flattened == true)
	{
		return new FygarPlayerFlattenedState;
	}

	if (fygar.m_InflationLevel != m_CurrentInflationState)
	{
		if (m_CurrentInflationState < 5)
		{
			m_CurrentInflationState = fygar.m_InflationLevel;

			switch (m_CurrentInflationState)
			{
			default:
				m_DeflationTimer = 0;
				[[fallthrough]];
			case 1:
				fygar.SetSprite(fygar.m_pInflatedSprite1);
				break;
			case 2:
				fygar.SetSprite(fygar.m_pInflatedSprite2);
				break;
			case 3:
				fygar.SetSprite(fygar.m_pInflatedSprite3);
				break;
			case 4:
				fygar.SetSprite(fygar.m_pInflatedSprite4);
				break;
			}
		}
	}

	if (m_CurrentInflationState >= 4)
	{
		m_DeathTimer -= static_cast<float>(deltaTime);
		if (m_DeathTimer <= 0)
		{
			fygar.Die();
			return new FygarPlayerNormalState;
		}
	}

	return nullptr;
}

void dae::FygarPlayerInflatedState::OnEnter(FygarPlayerController& fygar)
{
	m_CurrentInflationState = 1;
	fygar.SetSprite(fygar.m_pInflatedSprite1);
}

void dae::FygarPlayerInflatedState::OnExit(FygarPlayerController& fygar)
{
	fygar.m_InflationLevel = 0;
	fygar.GetFree();
}

FygarPlayerState* dae::FygarPlayerFlattenedState::Update(FygarPlayerController& fygar, const double deltaTime)
{
	m_DeathTimer -= static_cast<float>(deltaTime);
	if (m_DeathTimer <= 0)
	{
		fygar.CrushedByRock();
		return new FygarPlayerNormalState;
	}

	return nullptr;
}

void dae::FygarPlayerFlattenedState::OnEnter(FygarPlayerController& fygar)
{
	fygar.SetSprite(fygar.m_pFlattenedSprite);
}

void dae::FygarPlayerFlattenedState::OnExit(FygarPlayerController&)
{
}

FygarPlayerState* dae::FygarPlayerFireBreathingState::Update(FygarPlayerController&, const double deltaTime)
{
	if (m_BreathTime > 0)
	{
		m_BreathTime -= static_cast<float>(deltaTime);
	}

	if (m_BreathTime < 0)
	{
		return new FygarPlayerNormalState;
	}

    return nullptr;
}

void dae::FygarPlayerFireBreathingState::OnEnter(FygarPlayerController& fygar)
{
	ServiceLocator::GetSoundManager().Play(10, 100);
	fygar.ToggleFireBreath(true);
}

void dae::FygarPlayerFireBreathingState::OnExit(FygarPlayerController& fygar)
{
	fygar.ToggleFireBreath(false);
	fygar.m_BreatheFire = false;
}
