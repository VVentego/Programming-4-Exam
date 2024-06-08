#include "FygarState.h"

namespace dae
{
	FygarState* FygarNormalState::Update(FygarBehavior& fygar, const double deltaTime)
	{
		if (fygar.m_FireTimer < fygar.m_FireCooldown)
		{
			fygar.m_FireTimer += static_cast<float>(deltaTime);
		}

		m_StateTimer += static_cast<float>(deltaTime);

		if (fygar.m_Flattened == true)
		{
			return new FygarFlattenedState;
		}

		if (fygar.m_InflationLevel > 0 || fygar.m_IsHooked)
		{
			return new FygarInflatedState;
		}

		if (fygar.m_PlayersTransform.size() > 1)
		{
			fygar.SwapTarget(static_cast<float>(deltaTime));
		}

		if (!fygar.IsInTunnel())
		{
			return new FygarGhostState;
		}

		fygar.TrackPlayer();

		fygar.UpdateMovement();

		fygar.CheckForTunnel();

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

		if (fygar.m_FireTimer > fygar.m_FireCooldown)
		{
			return new FygarFireBreathingState;
		}

		if (m_StateTimer > m_NormalStateDuration)
		{
			return new FygarGhostState;
		}

		return nullptr;
	}

	void FygarNormalState::OnEnter(FygarBehavior& fygar)
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
		fygar.m_pOwner->SnapToGrid();
	}

	void FygarNormalState::OnExit(FygarBehavior&)
	{
	}

	FygarState* FygarGhostState::Update(FygarBehavior& fygar, const double deltaTime)
	{
		if (fygar.m_FireTimer < fygar.m_FireCooldown)
		{
			fygar.m_FireTimer += static_cast<float>(deltaTime);
		}
		m_StateTimer += static_cast<float>(deltaTime);

		if (fygar.m_Flattened == true)
		{
			return new FygarFlattenedState;
		}

		if (fygar.m_InflationLevel > 0 || fygar.m_IsHooked)
		{
			return new FygarInflatedState;
		}

		if (fygar.m_PlayersTransform.size() > 1)
		{
			fygar.SwapTarget(deltaTime);
		}

		fygar.GhostSeek();

		if (m_StateTimer > m_GhostStateDuration)
		{
			if (fygar.IsInTunnel())
			{
				return new FygarNormalState;
			}

			else
			{
				fygar.SeekNearestTunnel();
			}
		}

		return nullptr;
	}

	void FygarGhostState::OnEnter(FygarBehavior& fygar)
	{
		fygar.SetSprite(fygar.m_pGhostSheet);
		ServiceLocator::GetSoundManager().Play(5, 100);
	}

	void FygarGhostState::OnExit(FygarBehavior&)
	{
	}

	FygarState* FygarInflatedState::Update(FygarBehavior& fygar, const double deltaTime)
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
				return new FygarNormalState;
			}
			--fygar.m_InflationLevel;
		}

		if (fygar.m_Flattened == true)
		{
			return new FygarFlattenedState;
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
			}
		}

		return nullptr;
	}

	void FygarInflatedState::OnEnter(FygarBehavior& fygar)
	{
		m_CurrentInflationState = 1;
		fygar.SetSprite(fygar.m_pInflatedSprite1);
	}

	void FygarInflatedState::OnExit(FygarBehavior& fygar)
	{
		fygar.m_InflationLevel = 0;
		fygar.GetFree();
	}

	FygarState* FygarFlattenedState::Update(FygarBehavior& fygar, const double deltaTime)
	{
		m_DeathTimer -= static_cast<float>(deltaTime);
		if (m_DeathTimer <= 0)
		{
			fygar.CrushedByRock();
		}

		return nullptr;
	}

	void FygarFlattenedState::OnEnter(FygarBehavior& fygar)
	{
		ServiceLocator::GetSoundManager().Play(10, 100);
		fygar.SetSprite(fygar.m_pFlattenedSprite);
	}

	void FygarFlattenedState::OnExit(FygarBehavior&)
	{
	}

	FygarState* FygarFireBreathingState::Update(FygarBehavior&, const double deltaTime)
	{
		if (m_BreathTime > 0)
		{
			m_BreathTime -= static_cast<float>(deltaTime);
		}

		if (m_BreathTime < 0)
		{
			return new FygarNormalState;
		}

		return nullptr;
	}
	void FygarFireBreathingState::OnEnter(FygarBehavior& fygar)
	{
		fygar.ToggleFireBreath(true);
	}
	void FygarFireBreathingState::OnExit(FygarBehavior& fygar)
	{
		fygar.ToggleFireBreath(false);
		fygar.m_FireTimer = 0;
	}
}