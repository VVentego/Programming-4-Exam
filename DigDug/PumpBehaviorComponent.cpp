#include "PumpBehaviorComponent.h"
#include "../Minigin/TextureComponent.h"
#include "PookaBehavior.h"
#include "FygarBehavior.h"
#include <ColliderComponent.h>
#include "TunnelManager.h"

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

	if (m_Active && m_AttachedEnemy == nullptr)
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

		if (m_DistanceMoved < m_ShootDistance && IsInTunnel())
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
	if (!m_Hit && !m_Active)
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
		if (m_AttachedEnemy != nullptr)
		{
			if (m_AttachedEnemy->GetHooked() == false)
			{
				Reset();
				m_AttachedEnemy = nullptr;
				return;
			}

			m_AttachedEnemy->Inflate(m_PlayerIdx);
			
			soundManager.Play(1, 100);
		}
	}
}

void dae::PumpBehaviorComponent::CollisionEvent(GameObject* other)
{
	if (auto pooka = other->GetComponent<PookaBehavior>())
	{
		m_Hit = true;
		m_AttachedEnemy = pooka;
	}
	if (auto fygar = other->GetComponent<FygarBehavior>())
	{
		m_Hit = true;
		m_AttachedEnemy = fygar;
	}
}

void dae::PumpBehaviorComponent::Reset()
{
	m_Active = false;
	m_DistanceMoved = 0;
	m_TextureComponent->m_ShouldRender = false;
	m_Hit = false;
	m_AttachedEnemy = nullptr;
	m_pOwner->SetLocalPosition(0, 0);
}

const bool dae::PumpBehaviorComponent::IsInTunnel() const
{
	glm::vec2 checkPos0{};
	glm::vec2 checkPos1{};
	glm::vec2 checkPos2{};
	glm::vec2 currentPos{ m_pOwner->GetWorldPosition() };
	glm::vec2 size{ m_TextureComponent->GetSize() };

	const float offset{ 2.f };

	//Check in a line pattern from the tip of the pump back towards Dig Dug
	switch (m_FacingDirection)
	{
	case Facing::right:
		checkPos0 = currentPos + glm::vec2{ size.x, size.y / 2.f };
		checkPos1 = currentPos + glm::vec2{ size.x - offset, size.y / 2.f };
		checkPos2 = currentPos + glm::vec2{ size.x - offset * 2.f,size.y / 2.f };
		break;
	case Facing::down:
		checkPos0 = currentPos + glm::vec2{ size.x / 2.f, size.y };
		checkPos1 = currentPos + glm::vec2{ size.x / 2.f, size.y - offset };
		checkPos2 = currentPos + glm::vec2{ size.x / 2.f, size.y - offset * 2.f };
		break;
	case Facing::left:
		checkPos0 = currentPos + glm::vec2{ 0, size.y / 2.f };
		checkPos1 = currentPos + glm::vec2{ offset, size.y / 2.f };
		checkPos2 = currentPos + glm::vec2{ offset * 2.f, size.y / 2.f };
		break;
	case Facing::up:
		checkPos0 = currentPos + glm::vec2{ size.x / 2.f, 0 };
		checkPos1 = currentPos + glm::vec2{ size.x / 2.f, offset };
		checkPos2 = currentPos + glm::vec2{ size.x / 2.f, offset * 2.f };
		break;
	}

	//Check for a thin seperation or else return false
	auto& tunnelManager{ TunnelManager::GetInstance() };
	if (tunnelManager.InTunnel(checkPos0))
	{
		return true;
	}
	if (tunnelManager.InTunnel(checkPos1))
	{
		return true;
	}
	if (tunnelManager.InTunnel(checkPos2))
	{
		return true;
	}

	return false;
}