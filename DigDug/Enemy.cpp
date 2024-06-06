#include "Enemy.h"
#include "TunnelManager.h"
#include "PumpBehaviorComponent.h"

dae::Enemy::Enemy(GameObject* owner) :
	m_pEnemyOwner{ owner }
{
}

void dae::Enemy::AddPlayerToChase(GameObject* playerTransform)
{
	m_PlayersTransform.push_back(playerTransform);
}

void dae::Enemy::TrackPlayer()
{
	const glm::vec2 playerPos{ m_PlayersTransform[m_TargetIdx]->GetWorldPosition() };
	const glm::vec2 pookaPos{ m_pEnemyOwner->GetWorldPosition() };

	if (std::abs(playerPos.x - pookaPos.x) < 0.1f)
	{
		if (playerPos.y > pookaPos.y)
		{
			m_FacingDirection = Facing::up;
		}
		else
		{
			m_FacingDirection = Facing::down;
		}
	}
	else if (std::abs(playerPos.y - pookaPos.y) < 0.1f)
	{
		if (playerPos.x > pookaPos.x)
		{
			m_FacingDirection = Facing::right;
		}
		else
		{
			m_FacingDirection = Facing::left;
		}
	}
}

void dae::Enemy::Inflate(const int playerIdx)
{
	if (m_InflationLevel > 3) return;
	m_InflationLevel++;
	m_AttackingPlayerIdx = playerIdx;
}

void dae::Enemy::CheckForTunnel()
{
	glm::vec2 checkLocation{};
	glm::vec2 pos{ m_pEnemyOwner->GetWorldPosition() };
	const float size{ m_pAnimatorComponent->GetSize().x };
	switch (m_FacingDirection)
	{
	case Facing::right:
		checkLocation = pos + glm::vec2{ m_CheckDistance + size, size / 2 };
		break;
	case Facing::down:
		checkLocation = pos + glm::vec2{ size / 2, m_CheckDistance + size };
		break;
	case Facing::left:
		checkLocation = pos + glm::vec2{ -m_CheckDistance, size / 2 };
		break;
	case Facing::up:
		checkLocation = pos + glm::vec2{ size / 2, -m_CheckDistance };
		break;
	}

	auto& tunnelManager = TunnelManager::GetInstance();

	if (!tunnelManager.InTunnel(checkLocation))
	{
		FindNewDirection();
	}
}

void dae::Enemy::FindNewDirection()
{
	glm::vec2 checkLocation{};
	glm::vec2 pos{ m_pEnemyOwner->GetWorldPosition() };
	auto& tunnelManager = TunnelManager::GetInstance();
	const float size{ m_pAnimatorComponent->GetSize().x };
	switch (m_FacingDirection)
	{
	case Facing::right:
		checkLocation = pos + glm::vec2{ size / 2, m_CheckDistance + size };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::down;
			return;
		}
		checkLocation = pos + glm::vec2{ -m_CheckDistance, size / 2 };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::left;
			return;
		}
		checkLocation = pos + glm::vec2{ size / 2, -m_CheckDistance };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::up;
			return;
		}
		break;
	case Facing::down:
		checkLocation = pos + glm::vec2{ -m_CheckDistance, size / 2 };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::left;
			return;
		}
		checkLocation = pos + glm::vec2{ size / 2, -m_CheckDistance };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::up;
			return;
		}
		checkLocation = pos + glm::vec2{ m_CheckDistance + size, size / 2 };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::right;
			return;
		}
		break;
	case Facing::left:
		checkLocation = pos + glm::vec2{ size / 2, -m_CheckDistance };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::up;
			return;
		}
		checkLocation = pos + glm::vec2{ m_CheckDistance + size, size / 2 };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::right;
			return;
		}
		checkLocation = pos + glm::vec2{ size / 2, m_CheckDistance + size };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::down;
			return;
		}
		break;
	case Facing::up:
		checkLocation = pos + glm::vec2{ m_CheckDistance + size, size / 2 };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::right;
			return;
		}
		checkLocation = pos + glm::vec2{ size / 2, m_CheckDistance + size };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::down;
			return;
		}
		checkLocation = pos + glm::vec2{ -m_CheckDistance, size / 2 };
		if (tunnelManager.InTunnel(checkLocation))
		{
			m_FacingDirection = Facing::left;
			return;
		}
		break;
	}

}

void dae::Enemy::SetSprite(std::shared_ptr<SpriteSheet> spriteSheet)
{
	m_pAnimatorComponent->AddSpriteSheet(spriteSheet);
}

void dae::Enemy::SwapTarget(const double deltaTime)
{
	m_ChangeTargetTimer += static_cast<float>(deltaTime);

	if (m_ChangeTargetTimer > m_TimeToChangeTarget)
	{
		m_ChangeTargetTimer = 0;
		m_TargetIdx = std::rand() % m_PlayersTransform.size();
	}
}

void dae::Enemy::UpdateMovement()
{
	switch (m_FacingDirection)
	{
	case Facing::right:
		m_pEnemyOwner->SetLocalPosition(m_pEnemyOwner->GetLocalPosition() + glm::vec2{ m_Speed, 0 });
		break;
	case Facing::down:
		m_pEnemyOwner->SetLocalPosition(m_pEnemyOwner->GetLocalPosition() + glm::vec2{ 0, m_Speed });
		break;
	case Facing::left:
		m_pEnemyOwner->SetLocalPosition(m_pEnemyOwner->GetLocalPosition() + glm::vec2{ -m_Speed, 0 });
		break;
	case Facing::up:
		m_pEnemyOwner->SetLocalPosition(m_pEnemyOwner->GetLocalPosition() + glm::vec2{ 0, -m_Speed });
	}
}

void dae::Enemy::GhostSeek()
{
	const glm::vec2 playerPos{ m_PlayersTransform[m_TargetIdx]->GetWorldPosition() };
	const glm::vec2 currentPos{ m_pEnemyOwner->GetWorldPosition() };
	glm::vec2 direction = playerPos - currentPos;
	direction = glm::normalize(direction);
	direction *= m_Speed;

	m_pEnemyOwner->SetLocalPosition(m_pEnemyOwner->GetLocalPosition() + direction);
}

void dae::Enemy::SeekNearestTunnel()
{
	const glm::vec2 nearestTunnelPos = TunnelManager::GetInstance().FindNearestTunnel(m_pEnemyOwner->GetWorldPosition());
	const glm::vec2 pookaPos{ m_pEnemyOwner->GetWorldPosition() };

	if (std::abs(nearestTunnelPos.y - pookaPos.y) < 0.1f)
	{
		(nearestTunnelPos.x > pookaPos.x) ? m_FacingDirection = Facing::right : m_FacingDirection = Facing::left;
	}

	if (std::abs(nearestTunnelPos.x - pookaPos.x) < 0.1f)
	{
		(nearestTunnelPos.y > pookaPos.y) ? m_FacingDirection = Facing::down : m_FacingDirection = Facing::up;
	}
}

bool dae::Enemy::IsInTunnel() const
{
	glm::vec2 checkPos = m_pEnemyOwner->GetWorldPosition();
	const float size{ m_pAnimatorComponent->GetSize().x };
	checkPos += size;
	return TunnelManager::GetInstance().InTunnel(checkPos);
}

void dae::Enemy::CrushedByRock()
{
	ServiceLocator::GetSoundManager().Play(2, 100);

	m_pEnemyOwner->Destroy();
}

void dae::Enemy::GetFree()
{
	m_pPump->Reset();
	m_IsHooked = false;
	m_pPump = nullptr;
}