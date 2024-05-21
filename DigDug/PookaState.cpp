#include "PookaState.h"


using namespace dae;

PookaState* NormalState::Update(PookaBehavior& pooka, const double deltaTime)
{
	m_StateTimer += static_cast<float>(deltaTime);

	if (pooka.m_InflationLevel > 0)
	{
		return new InflatedState;
	}

	if (pooka.m_PlayersTransform.size() > 1)
	{
		pooka.SwapTarget(static_cast<float>(deltaTime));
	}

	if (!pooka.IsInTunnel())
	{
		return new GhostState;
	}

	pooka.CheckForTunnel();

	pooka.UpdateMovement();

	if (m_StateTimer > m_NormalStateDuration)
	{
		return new GhostState;
	}

	return nullptr;
}

void NormalState::OnEnter(PookaBehavior& pooka)
{
	pooka.SetSprite(pooka.m_pWalkSprite);
}

void NormalState::OnExit(PookaBehavior& pooka)
{
}

PookaState* GhostState::Update(PookaBehavior& pooka, const double deltaTime)
{
	m_StateTimer += static_cast<float>(deltaTime);

	if (pooka.m_InflationLevel > 0)
	{
		return new InflatedState;
	}

	if (pooka.m_PlayersTransform.size() > 1)
	{
		pooka.SwapTarget(deltaTime);
	}

	pooka.TrackPlayer();

	pooka.UpdateMovement();

	if (m_StateTimer > m_GhostStateDuration)
	{
		if (pooka.IsInTunnel())
		{
			return new NormalState;
		}

		else
		{
			pooka.SeekNearestTunnel();
		}
	}

	return nullptr;
}

void GhostState::OnEnter(PookaBehavior& pooka)
{
	pooka.SetSprite(pooka.m_pGhostSheet);
}

void GhostState::OnExit(PookaBehavior& pooka)
{
}

PookaState* InflatedState::Update(PookaBehavior& pooka, const double deltaTime)
{
	if (m_CurrentInflationState > 3)
	{
		m_DeflationTimer += static_cast<float>(deltaTime);
	}

	if (m_DeflationTimer > m_TimeToDeflate)
	{
		--pooka.m_InflationLevel;
	}

	if (pooka.m_InflationLevel != m_CurrentInflationState)
	{
		if (m_CurrentInflationState < 5)
		{
			m_CurrentInflationState = pooka.m_InflationLevel;

			switch (m_CurrentInflationState)
			{
			default:
				m_DeflationTimer = 0;
				[[fallthrough]];
			case 1: 
				pooka.SetSprite(pooka.m_pInflatedSprite1);
				break;
			case 2:
				pooka.SetSprite(pooka.m_pInflatedSprite2);
				break;
			case 3:
				pooka.SetSprite(pooka.m_pInflatedSprite3);
				break;
			case 4:
				pooka.SetSprite(pooka.m_pInflatedSprite4);
				break;
			}
		}
	}

	if (m_CurrentInflationState >= 4)
	{
		m_DeathTimer -= static_cast<float>(deltaTime);
		if (m_DeathTimer <= 0)
		{
			pooka.Die();
		}
	}

	if (pooka.m_InflationLevel <= 0)
	{

		return new NormalState;
	}

	return nullptr;
}

void InflatedState::OnEnter(PookaBehavior& pooka)
{
	m_CurrentInflationState = 1;
	pooka.SetSprite(pooka.m_pInflatedSprite1);
}

void InflatedState::OnExit(PookaBehavior& pooka)
{
	pooka.m_InflationLevel = 0;
}
