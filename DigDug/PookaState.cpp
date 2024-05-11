#include "PookaState.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

dae::PookaState* dae::NormalState::Update(PookaBehavior& pooka, const double deltaTime)
{
	m_StateTimer += deltaTime;

	if (pooka.m_PlayersTransform.size() > 1)
	{
		pooka.m_ChangeTargetTimer += static_cast<float>(deltaTime);

		if (pooka.m_ChangeTargetTimer > pooka.m_TimeToChangeTarget)
		{
			pooka.m_ChangeTargetTimer = 0;
			pooka.m_TargetIdx = std::rand() % pooka.m_PlayersTransform.size();
		}
	}

	pooka.CheckForTunnel();

	switch (pooka.m_FacingDirection)
	{
	case Facing::right:
		pooka.m_pOwner->SetLocalPosition(pooka.m_pOwner->GetLocalPosition() + glm::vec2{ pooka.m_Speed, 0 });
		break;
	case Facing::down:
		pooka.m_pOwner->SetLocalPosition(pooka.m_pOwner->GetLocalPosition() + glm::vec2{ 0, -pooka.m_Speed });
		break;
	case Facing::left:
		pooka.m_pOwner->SetLocalPosition(pooka.m_pOwner->GetLocalPosition() + glm::vec2{ -pooka.m_Speed, 0 });
		break;
	case Facing::up:
		pooka.m_pOwner->SetLocalPosition(pooka.m_pOwner->GetLocalPosition() + glm::vec2{ 0, pooka.m_Speed });
	}

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
		pooka.m_ChangeTargetTimer += static_cast<float>(deltaTime);

		if (pooka.m_ChangeTargetTimer > pooka.m_TimeToChangeTarget)
		{
			pooka.m_ChangeTargetTimer = 0;
			pooka.m_TargetIdx = std::rand() % pooka.m_PlayersTransform.size();
		}
	}

	pooka.TrackPlayer();

	switch (pooka.m_FacingDirection)
	{
	case Facing::right:
		pooka.m_pOwner->SetLocalPosition(pooka.m_pOwner->GetLocalPosition() + glm::vec2{ pooka.m_Speed, 0 });
		break;
	case Facing::down:
		pooka.m_pOwner->SetLocalPosition(pooka.m_pOwner->GetLocalPosition() + glm::vec2{ 0, -pooka.m_Speed });
		break;
	case Facing::left:
		pooka.m_pOwner->SetLocalPosition(pooka.m_pOwner->GetLocalPosition() + glm::vec2{ -pooka.m_Speed, 0 });
		break;
	case Facing::up:
		pooka.m_pOwner->SetLocalPosition(pooka.m_pOwner->GetLocalPosition() + glm::vec2{ 0, pooka.m_Speed });
	}

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
