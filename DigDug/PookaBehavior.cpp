#include "PookaBehavior.h"
#include "PumpBehaviorComponent.h"
#include "PookaState.h"
#include "TunnelManager.h"
#include "../Minigin/SpriteAnimatorComponent.h"

dae::PookaBehavior::PookaBehavior(GameObject* pOwner) :
	Component(pOwner), m_CurrentState{ new dae::NormalState },
	m_pWalkSprite{ std::make_shared<SpriteSheet>("PookaMoveRight.png", 1, 2) },
	m_pGhostSheet{ std::make_shared<SpriteSheet>("PookaGhost.png", 1, 2) }
{
	auto pookaSpriteAnimator = std::make_unique<dae::SpriteAnimatorComponent>(pOwner);
	pookaSpriteAnimator->AddSpriteSheet(m_pWalkSprite);
	m_pAnimatorComponent = pookaSpriteAnimator.get();
	pOwner->AddComponent(std::move(pookaSpriteAnimator));
	m_TargetIdx = 0;
}

dae::PookaBehavior::~PookaBehavior()
{
	if (m_CurrentState != nullptr)
	{
		delete m_CurrentState;
		m_CurrentState = nullptr;
	}
}

void dae::PookaBehavior::Update(const double deltaTime)
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

void dae::PookaBehavior::AddPlayerToChase(GameObject* playerTransform)
{
	m_PlayersTransform.push_back(playerTransform);
}

void dae::PookaBehavior::CollisionEvent(GameObject* other)
{
	if(other == nullptr)
	{
		return;
	}

	if (auto pump = other->GetComponent<PumpBehaviorComponent>())
	{
		if (pump->IsActive())
		{
			ServiceLocator::GetSoundManager().Play(1, 50);
		}
	}
}

void dae::PookaBehavior::TrackPlayer()
{
	const glm::vec2 playerPos{ m_PlayersTransform[m_TargetIdx]->GetWorldPosition() };
	const glm::vec2 pookaPos{ m_pOwner->GetWorldPosition() };

		if (std::abs(playerPos.y - pookaPos.y) < 0.1f)
		{
			(playerPos.x > pookaPos.x) ? m_FacingDirection = Facing::right : m_FacingDirection = Facing::left;
		}

		if (std::abs(playerPos.x - pookaPos.x) < 0.1f)
		{
			(playerPos.y > pookaPos.y) ? m_FacingDirection = Facing::up : m_FacingDirection = Facing::down;
		}
}

void dae::PookaBehavior::CheckForTunnel()
{
	glm::vec2 checkLocation{};
	switch (m_FacingDirection)
	{
	case Facing::right:
		checkLocation = m_pOwner->GetWorldPosition() + glm::vec2{ m_CheckDistance + m_Size, m_Size / 2 };
		break;
	case Facing::down:
		checkLocation = m_pOwner->GetWorldPosition() + glm::vec2{ m_Size / 2, -m_CheckDistance };
		break;
	case Facing::left:
		checkLocation = m_pOwner->GetWorldPosition() + glm::vec2{ -m_CheckDistance, m_Size / 2 };
		break;
	case Facing::up:
		checkLocation = m_pOwner->GetWorldPosition() + glm::vec2{ m_Size / 2, m_CheckDistance + m_Size };
		break;
	}

	auto& tunnelManager = TunnelManager::GetInstance();

	if (!tunnelManager.InTunnel(checkLocation))
	{
		ReverseDirection();
	}
}

void dae::PookaBehavior::ReverseDirection()
{
	switch (m_FacingDirection)
	{
	case Facing::right:
		m_FacingDirection = Facing::left;
		break;
	case Facing::down:
		m_FacingDirection = Facing::up;
		break;
	case Facing::left:
		m_FacingDirection = Facing::right;
		break;
	case Facing::up:
		m_FacingDirection = Facing::down;
		break;
	}
	m_BumpedRecently = true;
}

void dae::PookaBehavior::SetSprite(std::shared_ptr<SpriteSheet> spriteSheet)
{
	m_pAnimatorComponent->AddSpriteSheet(spriteSheet);
}
