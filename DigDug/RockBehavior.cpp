#include "RockBehavior.h"
#include "RockState.h"
#include "TunnelManager.h"
#include "DigDugController.h"
#include "Enemy.h"

dae::RockBehavior::RockBehavior(GameObject* pOwner) :
	Component(pOwner),
	m_pNormalRockSprite{ std::make_shared<SpriteSheet>("RockIdle.png", 1, 1) },
	m_pFallingRockSprite{ std::make_shared<SpriteSheet>("RockFalling.png", 1, 1) },
	m_pBreakingRockSprite{ std::make_shared<SpriteSheet>("RockBreaking.png", 1, 2) },
	m_CurrentState{ new RockIdleState }
{
	auto spriteAnimator = std::make_unique<SpriteAnimatorComponent>(pOwner);
	spriteAnimator->AddSpriteSheet(m_pNormalRockSprite);
	m_pAnimatorComponent = spriteAnimator.get();
	pOwner->AddComponent(std::move(spriteAnimator));
}

dae::RockBehavior::~RockBehavior()
{
	if (m_CurrentState != nullptr)
	{
		delete m_CurrentState;
		m_CurrentState = nullptr;
	}
}

void dae::RockBehavior::Update(const double deltaTime)
{
	auto nextState = m_CurrentState->Update(*this, deltaTime);

	if (nextState != nullptr)
	{
		m_CurrentState->OnExit(*this);
		delete m_CurrentState;
		m_CurrentState = nextState;
		m_CurrentState->OnEnter(*this);
	}
}

void dae::RockBehavior::AddPlayer(GameObject* player)
{
	m_pPlayers.push_back(player);
}

void dae::RockBehavior::SetSprite(std::shared_ptr<SpriteSheet> spriteSheet)
{
	m_pAnimatorComponent->AddSpriteSheet(spriteSheet);
}

void dae::RockBehavior::Fall(const double deltaTime)
{
	glm::vec2 newPosition{ m_pOwner->GetWorldPosition() };
	newPosition.y += m_FallSpeed * static_cast<float>(deltaTime);

	m_pOwner->SetWorldPosition(newPosition.x, newPosition.y);
}

const bool dae::RockBehavior::IsInTunnel() const
{
	const glm::vec2 currentPos = m_pOwner->GetWorldPosition();
	const float size{ m_pAnimatorComponent->GetSize().x };
	const glm::vec2 checkPos0{ currentPos.x, currentPos.y + size + m_TunnelCheckOffset };
	const glm::vec2 checkPos1{ currentPos.x + size / 2.f, currentPos.y + size + m_TunnelCheckOffset };
	const glm::vec2 checkPos2{ currentPos.x + size, currentPos.y + size + m_TunnelCheckOffset };

	auto& tunnelManager = TunnelManager::GetInstance();

	//Only return true if all points are not in tunnel.
	if (!tunnelManager.InTunnel(checkPos0))
	{
		return false;
	}
	if (!tunnelManager.InTunnel(checkPos1))
	{
		return false;
	}
	if (!tunnelManager.InTunnel(checkPos2))
	{
		return false;
	}

	return true;
}

const bool dae::RockBehavior::DeepCheckInTunnel() const
{
	const glm::vec2 currentPos = m_pOwner->GetWorldPosition();
	const float size{ m_pAnimatorComponent->GetSize().x };
	const glm::vec2 checkPos0{ currentPos.x + size / 2.f, currentPos.y + size / 2.f };
	const glm::vec2 checkPos1{ currentPos.x + size / 2.f, currentPos.y + size };
	const glm::vec2 checkPos2{ currentPos.x + size / 2.f, currentPos.y + size + m_TunnelCheckOffset };

	auto& tunnelManager = TunnelManager::GetInstance();

	//Only return true if all points are not in tunnel.
	if (!tunnelManager.InTunnel(checkPos0))
	{
		return false;
	}
	if (!tunnelManager.InTunnel(checkPos1))
	{
		return false;
	}
	if (!tunnelManager.InTunnel(checkPos2))
	{
		return false;
	}

	return true;
}

void dae::RockBehavior::Die()
{
	Event event{};
	event.type = EventType::ENEMY_KILLED;
	event.stringValue = "Rocked" + m_InstigatingPlayerName.back();
	event.intValue = m_KillCount;
	EventObserver::GetInstance().Notify(event);

	m_pOwner->Destroy();
}

bool dae::RockBehavior::IsDoneDying()
{
	if (m_pAnimatorComponent->RenderOnce())
	{
		return true;
	}

	return false;
}

dae::GameObject* dae::RockBehavior::GetNearestPlayer()
{
	float closestPlayerDistance{};
	GameObject* closestPlayer{};

	if (m_pPlayers.empty())
	{
		return nullptr;
	}

	if (m_pPlayers.size() == static_cast<size_t>(1))
	{
		return m_pPlayers.front();
	}

	for (GameObject* player : m_pPlayers)
	{
		const glm::vec2 playerPos = player->GetWorldPosition();
		const float distance = glm::distance(m_pOwner->GetWorldPosition(), playerPos);

		if (distance < closestPlayerDistance)
		{
			closestPlayerDistance = distance;
			closestPlayer = player;
		}
	}

	return closestPlayer;
}

void dae::RockBehavior::SetInstigatingPlayer()
{
	GameObject* player = GetNearestPlayer();
	if (player != nullptr)
	{
		if (DigDugController* digDug = player->GetComponent<DigDugController>())
		{
			m_InstigatingPlayerName = digDug->m_PlayerName;
		}
	}
}

void dae::RockBehavior::CollisionEvent(GameObject* other)
{
	if (m_CanKill == false) return;

	if (auto enemy = other->GetComponent<Enemy>())
	{
		if (enemy->Flatten())
		{
			++m_KillCount;
		}
	}
}

const std::string& dae::RockBehavior::GetInstigatingPlayer() const
{
	return m_InstigatingPlayerName;
}
