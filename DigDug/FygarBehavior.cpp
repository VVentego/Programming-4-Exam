#include "FygarBehavior.h"
#include "PumpBehaviorComponent.h"
#include "RockBehavior.h"
#include "FygarState.h"
#include "FygarBreathComponent.h"

dae::FygarBehavior::FygarBehavior(GameObject* pOwner, FygarBreathComponent* pFygarBreathComponent) :
	Component(pOwner), Enemy(pOwner), m_CurrentState{ new FygarNormalState },
	m_FygarBreathComponent{ pFygarBreathComponent },
	m_pWalkLeftSprite{ std::make_shared<SpriteSheet>("FygarLeft.png", 1, 2) },
	m_pWalkRightSprite{ std::make_shared<SpriteSheet>("FygarRight.png", 1, 2) },
	m_pGhostSheet{ std::make_shared<SpriteSheet>("FygarGhost.png", 1, 2) },
	m_pInflatedSprite1{ std::make_shared<SpriteSheet>("FygarInflated1.png", 1, 1) },
	m_pInflatedSprite2{ std::make_shared<SpriteSheet>("FygarInflated2.png", 1, 1) },
	m_pInflatedSprite3{ std::make_shared<SpriteSheet>("FygarInflated3.png", 1, 1) },
	m_pInflatedSprite4{ std::make_shared<SpriteSheet>("FygarInflated4.png", 1, 1) },
	m_pFlattenedSprite{ std::make_shared<SpriteSheet>("FygarFlat.png", 1, 1) }
{
	auto fygarSpriteAnimator = std::make_unique<dae::SpriteAnimatorComponent>(pOwner);
	fygarSpriteAnimator->AddSpriteSheet(m_pWalkLeftSprite);
	m_pAnimatorComponent = fygarSpriteAnimator.get();
	pOwner->AddComponent(std::move(fygarSpriteAnimator));
	m_TargetIdx = 0;
}

dae::FygarBehavior::~FygarBehavior()
{
	if (m_CurrentState != nullptr)
	{
		delete m_CurrentState;
		m_CurrentState = nullptr;
	}
}

void dae::FygarBehavior::Update(const double deltaTime)
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

void dae::FygarBehavior::Die()
{
	ServiceLocator::GetSoundManager().Play(3, 100);
	ServiceLocator::GetSoundManager().Play(2, 100);
	m_pPump->Reset();
	Event enemyKilledEvent;

	//Notify event is passed to player and then player passes on a score gained event depending on depth
	enemyKilledEvent.type = EventType::ENEMY_KILLED;
	enemyKilledEvent.stringValue = "Fygar" + std::to_string(m_AttackingPlayerIdx);
	NotifyObserver(enemyKilledEvent);

	m_pOwner->Destroy();
}

bool dae::FygarBehavior::PlayerInRange()
{
	const glm::vec2 playerPos{ m_PlayersTransform[m_TargetIdx]->GetWorldPosition() };
	const glm::vec2 currentPos{ m_pOwner->GetWorldPosition() };
	glm::vec2 size{ m_pAnimatorComponent->GetSize() };

	//Facing right
	if (float distance = currentPos.x - playerPos.x > 0 && (m_FacingDirection == Facing::right || m_FacingDirection == Facing::up))
	{
		if (std::abs(distance) < m_FireRange + size.x)
		{
			return true;
		}
	}
	//Facing left
	else
	{
		if (std::abs(distance) < m_FireRange)
		{
			return true;
		}
	}
	return false;
}

void dae::FygarBehavior::ToggleFireBreath(const bool active)
{
	bool facingRight{};
	const glm::vec2 fygarPos{ m_pOwner->GetWorldPosition() };
	if (m_FacingDirection == Facing::right || m_FacingDirection == Facing::up)
	{
		facingRight = true;
		m_FygarBreathComponent->SetLocalPosition(glm::vec2{ m_pAnimatorComponent->GetSize().x, 0 });
	}

	else
	{
		m_FygarBreathComponent->SetLocalPosition(glm::vec2{ 0, 0 });
	}

	m_FygarBreathComponent->Toggle(active, facingRight);
}

void dae::FygarBehavior::CollisionEvent(GameObject* other)
{
	if (other == nullptr)
	{
		return;
	}
	if (auto pump = other->GetComponent<PumpBehaviorComponent>())
	{
		if (pump->IsActive())
		{
			if (!m_IsHooked)
			{
				m_pPump = pump;
				ServiceLocator::GetSoundManager().Play(1, 50);
				m_IsHooked = true;
			}
		}
	}
	if (auto rock = other->GetComponent<RockBehavior>())
	{
		if (rock->CanKill())
		{
			m_AttackingPlayerIdx = rock->GetInstigatingPlayer().back();
			m_Flattened = true;
		}
	}
}