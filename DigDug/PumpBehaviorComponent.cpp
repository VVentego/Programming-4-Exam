#include "PumpBehaviorComponent.h"
#include "../Minigin/TextureComponent.h"
#include "PookaBehavior.h"
#include <ColliderComponent.h>

dae::PumpBehaviorComponent::PumpBehaviorComponent(GameObject* pOwner, const int playerIdx) :
	Component::Component(pOwner), m_PlayerIdx{ playerIdx }
{
	auto& resourceManager = ResourceManager::GetInstance();

	m_Textures.push_back(resourceManager.LoadTexture("PumpRight.png"));
	m_Textures.push_back(resourceManager.LoadTexture("PumpDown.png"));
	m_Textures.push_back(resourceManager.LoadTexture("PumpLeft.png"));
	m_Textures.push_back(resourceManager.LoadTexture("PumpUp.png"));

	pOwner->AddComponent(std::make_unique<dae::TextureComponent>(pOwner));
	m_TextureComponent = pOwner->GetComponent <dae::TextureComponent>();

	m_TextureComponent->m_ShouldRender = false;
	m_TextureComponent->SetTexture(m_Textures[0]);
}


void dae::PumpBehaviorComponent::Update(const double deltaTime)
{
	glm::vec2 velocity{};

	if (m_Active && m_AttachedPooka == nullptr)
	{
		glm::vec2 currentPos{ m_pOwner->GetLocalPosition() };
		switch (m_FacingDirection)
		{
		case Facing::right:
			velocity.x = m_Speed;
			break;
		case Facing::down:
			velocity.y = m_Speed;
			break;
		case Facing::left:
			velocity.x = -m_Speed;
			break;
		case Facing::up:
			velocity.y = -m_Speed;
			break;
		}

		if (m_DistanceMoved < m_ShootDistance)
		{
			m_pOwner->SetLocalPosition(currentPos.x + velocity.x * static_cast<float>(deltaTime),
				currentPos.y + velocity.y * static_cast<float>(deltaTime));

			m_DistanceMoved += m_Speed * static_cast<float>(deltaTime);
		}
		else
		{
			Reset();
		}
	}
}

void dae::PumpBehaviorComponent::Fire(const Facing direction)
{
	auto& soundManager = ServiceLocator::GetSoundManager();
	if (!m_Hit)
	{
		m_Active = true;
		m_TextureComponent->m_ShouldRender = true;

		m_FacingDirection = direction;
		if (static_cast<unsigned int>(m_FacingDirection) <= m_Textures.size())
		{
			m_TextureComponent->SetTexture(m_Textures[static_cast<int>(m_FacingDirection)]);
			m_pOwner->GetCollider()->UpdateColliderSize(m_TextureComponent->GetSize());
		}

		soundManager.Play(0, 100);
	}

	else
	{
		if (m_AttachedPooka != nullptr)
		{
			if (m_AttachedPooka->GetHooked() == false)
			{
				Reset();
				m_AttachedPooka = nullptr;
				return;
			}

			m_AttachedPooka->Inflate(m_PlayerIdx);
			
			soundManager.Play(1, 100);
		}
	}
}

void dae::PumpBehaviorComponent::CollisionEvent(GameObject* other)
{
	if (auto pooka = other->GetComponent<PookaBehavior>())
	{
		m_Hit = true;
		m_AttachedPooka = pooka;
	}
}

void dae::PumpBehaviorComponent::Reset()
{
	m_Active = false;
	m_DistanceMoved = 0;
	m_TextureComponent->m_ShouldRender = false;
	m_Hit = false;
	m_AttachedPooka = nullptr;
	m_pOwner->SetLocalPosition(0, 0);
}