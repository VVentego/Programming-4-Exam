#include "PookaBehavior.h"
#include "PumpBehaviorComponent.h"
#include "PookaState.h"
#include "TunnelManager.h"
#include "../Minigin/SpriteAnimatorComponent.h"
#include "RockBehavior.h"

dae::PookaBehavior::PookaBehavior(GameObject* pOwner) :
	Component(pOwner), Enemy(pOwner), m_CurrentState{ new PookaNormalState },
	m_pWalkLeftSprite{ std::make_shared<SpriteSheet>("PookaMoveLeft.png", 1, 2) },
	m_pWalkRightSprite{ std::make_shared<SpriteSheet>("PookaMoveRight.png", 1, 2) },
	m_pGhostSheet{ std::make_shared<SpriteSheet>("PookaGhost.png", 1, 2) },
	m_pInflatedSprite1{ std::make_shared<SpriteSheet>("PookaInflate1.png", 1, 1) },
	m_pInflatedSprite2{ std::make_shared<SpriteSheet>("PookaInflate2.png", 1, 1) },
	m_pInflatedSprite3{ std::make_shared<SpriteSheet>("PookaInflate3.png", 1, 1) },
	m_pInflatedSprite4{ std::make_shared<SpriteSheet>("PookaInflate4.png", 1, 1) },
	m_pFlattenedSprite{ std::make_shared<SpriteSheet>("PookaFlat.png", 1, 1) }
{
	auto pookaSpriteAnimator = std::make_unique<dae::SpriteAnimatorComponent>(pOwner);
	pookaSpriteAnimator->AddSpriteSheet(m_pWalkLeftSprite);
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

void dae::PookaBehavior::CollisionEvent(GameObject* other)
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

void dae::PookaBehavior::Die()
{
	ServiceLocator::GetSoundManager().Play(3, 100);
	ServiceLocator::GetSoundManager().Play(2, 100);
	m_pPump->Reset();
	Event enemyKilledEvent;

	//Notify event is passed to player and then player passes on a score gained event depending on depth
	enemyKilledEvent.type = EventType::ENEMY_KILLED;
	enemyKilledEvent.stringValue = "Pooka" + std::to_string(m_AttackingPlayerIdx);
	NotifyObserver(enemyKilledEvent);

	m_pOwner->Destroy();
}

void dae::PookaBehavior::CrushedByRock()
{
	Event event{};
	event.type = EventType::ENEMY_KILLED;
	event.stringValue = "Pooka";

	NotifyObserver(event);
	Enemy::CrushedByRock();
}
