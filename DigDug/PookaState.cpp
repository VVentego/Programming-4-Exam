#include "PookaState.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

dae::PookaState* dae::NormalState::Update(PookaBehavior& pooka, const double deltaTime)
{
	m_StateTimer += deltaTime;

	if (pooka.m_PlayersTransform.size() > 1)
	{
		pooka.SwapTarget(deltaTime);
	}

	pooka.CheckForTunnel();

	pooka.UpdateMovement();

	if (m_StateTimer > m_NormalStateDuration)
	{
#ifdef _DEBUG
		std::cout << "Pooka State changed to ghost state!" << std::endl;
#endif // _DEBUG
		return new GhostState;
	}

	return nullptr;
}

void dae::NormalState::OnEnter(PookaBehavior& pooka)
{
	pooka.SetSprite(pooka.m_pWalkSprite);
}

void dae::NormalState::OnExit(PookaBehavior& pooka)
{
}

dae::PookaState* dae::GhostState::Update(PookaBehavior& pooka, const double deltaTime)
{
	m_StateTimer += deltaTime;

	if (pooka.m_PlayersTransform.size() > 1)
	{
		pooka.SwapTarget(deltaTime);
	}

	pooka.TrackPlayer();

	pooka.UpdateMovement();

	if (m_StateTimer > m_GhostStateDuration)
	{
#ifdef _DEBUG
		std::cout << "Pooka State changed to normal state!" << std::endl;
#endif // _DEBUG
		return new NormalState;
	}

	return nullptr;
}

void dae::GhostState::OnEnter(PookaBehavior& pooka)
{
	pooka.SetSprite(pooka.m_pGhostSheet);
}

void dae::GhostState::OnExit(PookaBehavior& pooka)
{
}
