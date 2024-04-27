#include "PumpBehaviorComponent.h"
#include "../Minigin/TextureComponent.h"

dae::PumpBehaviorComponent::PumpBehaviorComponent(GameObject* pOwner, std::vector<std::shared_ptr<Texture2D>> textures) :
	Component::Component(pOwner), m_Textures{ textures }
{
	m_TextureComponent = pOwner->GetComponent<TextureComponent>();
	assert(m_TextureComponent != nullptr);

	m_TextureComponent->m_ShouldRender = false;
	m_TextureComponent->SetTexture(m_Textures[0]);
}


void dae::PumpBehaviorComponent::Update(const double deltaTime)
{
	glm::vec2 velocity{};
	if (m_Active)
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
			m_Active = false;
			m_DistanceMoved = 0;
			m_TextureComponent->m_ShouldRender = false;
			m_pOwner->SetLocalPosition(0, 0);
		}
	}
}

void dae::PumpBehaviorComponent::Fire(const Facing direction)
{
	m_Active = true;
	m_TextureComponent->m_ShouldRender = true;

	m_FacingDirection = direction;
	if (static_cast<unsigned int>(m_FacingDirection) <= m_Textures.size())
	{
		m_TextureComponent->SetTexture(m_Textures[static_cast<int>(m_FacingDirection)]);
	}
	auto& soundManager = ServiceLocator::GetInstance().GetSoundManager();

	soundManager.Play(0, 100);
}
