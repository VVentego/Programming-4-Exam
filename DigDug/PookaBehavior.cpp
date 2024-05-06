#include "PookaBehavior.h"
#include "PumpBehaviorComponent.h"
#include "PookaState.h"

dae::PookaBehavior::PookaBehavior(GameObject* pOwner) :
	Component(pOwner), m_CurrentState{ new dae::NormalState }
{
	m_TargetIdx = std::rand() % m_PlayersTransform.size();
}

dae::PookaBehavior::~PookaBehavior()
{
	delete m_CurrentState;
	m_CurrentState = nullptr;
}

void dae::PookaBehavior::Update(const double deltaTime)
{
	if (m_PlayersTransform.size() > 1)
	{
		m_ChangeTargetTimer += static_cast<float>(deltaTime);

		if (m_ChangeTargetTimer > m_TimeToChangeTarget)
		{
			m_ChangeTargetTimer = 0;
			m_TargetIdx = std::rand() % m_PlayersTransform.size();
		}
	}
}

void dae::PookaBehavior::AddPlayerToChase(const Transform* playerTransform)
{
	m_PlayersTransform.push_back(playerTransform);
}

void dae::PookaBehavior::CollisionEvent(GameObject* other)
{
	auto collidedObject = other->GetComponent<PumpBehaviorComponent>();
	if (collidedObject != nullptr && collidedObject->IsActive())
	{
		ServiceLocator::GetSoundManager().Play(1, 50);
	}
}

void dae::PookaBehavior::TrackPlayer()
{
	const glm::vec2 playerPos{ m_PlayersTransform[m_TargetIdx]->GetWorldPosition() };
	const glm::vec2 pookaPos{ m_pOwner->GetWorldPosition() };

	if (m_BumpedRecently == false)
	{
		if (std::abs(playerPos.y - pookaPos.y) < 0.1f)
		{
			(playerPos.x > m_pOwner->GetWorldPosition().x) ? m_FacingDirection = Facing::left : m_FacingDirection = Facing::right;
		}

		if (std::abs(playerPos.x - pookaPos.x) < 0.1f)
		{
			(playerPos.y > m_pOwner->GetWorldPosition().y) ? m_FacingDirection = Facing::up : m_FacingDirection = Facing::down;
		}
	}
}
