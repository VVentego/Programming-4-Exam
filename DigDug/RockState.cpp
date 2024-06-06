#include "RockState.h"
dae::RockState* dae::RockIdleState::Update(RockBehavior& rock, const double)
{
	if (rock.IsInTunnel())
	{
		return new RockFallingState;
	}

	return nullptr;
}

void dae::RockIdleState::OnEnter(RockBehavior& rock)
{
	rock.SetSprite(rock.m_pNormalRockSprite);
}

void dae::RockIdleState::OnExit(RockBehavior&)
{
}

dae::RockState* dae::RockFallingState::Update(RockBehavior& rock, const double deltaTime)
{
	if (m_FallDelay < 0)
	{
		rock.Fall(deltaTime);
		m_MinimumFallDistance -= rock.m_FallSpeed * static_cast<float>(deltaTime);
	}

	if (!rock.DeepCheckInTunnel() && m_MinimumFallDistance <= 0)
	{
		return new RockBreakState;
	}

	else
	{
		m_FallDelay -= static_cast<float>(deltaTime);
	}

	return nullptr;
}

void dae::RockFallingState::OnEnter(RockBehavior& rock)
{
	rock.SetSprite(rock.m_pFallingRockSprite);
	rock.m_CanKill = true;
	rock.SetInstigatingPlayer();
}

void dae::RockFallingState::OnExit(RockBehavior&)
{
}

dae::RockState* dae::RockBreakState::Update(RockBehavior& rock, const double)
{
	if (rock.IsDoneDying())
	{
		rock.Die();
	}
	return nullptr;
}

void dae::RockBreakState::OnEnter(RockBehavior& rock)
{
	rock.SetSprite(rock.m_pBreakingRockSprite);
	rock.m_CanKill = false;
}

void dae::RockBreakState::OnExit(RockBehavior&)
{
}
