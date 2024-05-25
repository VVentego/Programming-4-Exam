#include "DigDugState.h"
#include "Enemy.h"

using namespace dae;

DigDugState* DigDugNormalState::Update(DigDugController& digDug, const double deltaTime)
{
	if (m_InvulnerabilityTimer > 0)
	{
		--m_InvulnerabilityTimer;
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
		digDug.StopMusic();
		digDug.m_Velocity = {};
	}

	if (m_Dead)
	{
		return new DigDugDeathState;
	}

	if (!digDug.InTunnel())
	{
		return new DigDugDigState;
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
}

void dae::DigDugNormalState::OnExit(DigDugController& digDug) 
{
	digDug.StopMusic();
}


void DigDugNormalState::HandleInput(DigDugController& digdug, Command* command) 
{
	if (command != nullptr)
	{
		if (digdug.m_DistanceMoved < digdug.m_MoveStepDistance) return;
		command->Execute(&digdug);
	}
}

void dae::DigDugNormalState::HandleCollision(DigDugController&, GameObject* other)
{ 
	if (other == nullptr or m_InvulnerabilityTimer > 0)
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
}

DigDugState* DigDugDeathState::Update(DigDugController& digDug, const double)
{
	if (digDug.IsDoneDying())
	{
		return new DigDugNormalState;
	}

	return nullptr;
}

void DigDugDeathState::OnEnter(DigDugController& digDug)
{
	digDug.SetSpriteSheet(digDug.m_pDeathSprite, 0.5);
}

void DigDugDeathState::OnExit(DigDugController& digDug)
{
	digDug.OnPlayerDeath();
}

DigDugState* dae::DigDugDigState::Update(DigDugController& digDug, const double deltaTime)
{
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

	else
	{
		digDug.StopMusic();
		digDug.m_Velocity = {};
		digDug.DigTunnel();
	}

	if (m_Dead)
	{
		return new DigDugDeathState;
	}


	if (digDug.InTunnel())
	{
		return new DigDugNormalState;
	}
	return nullptr;
}

void dae::DigDugDigState::OnEnter(DigDugController& digDug)
{
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
	digDug.StopMusic();
}

void dae::DigDugDigState::HandleInput(DigDugController& digDug, Command* command)
{
	if (command != nullptr)
	{
		if (digDug.m_DistanceMoved < digDug.m_MoveStepDistance) return;
		command->Execute(&digDug);
	}
}

void dae::DigDugDigState::HandleCollision(DigDugController&, GameObject* other)
{
	if (other == nullptr)
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
}
