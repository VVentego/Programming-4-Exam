#include "FygarBreathComponent.h"
#include <ColliderComponent.h>

dae::FygarBreathComponent::FygarBreathComponent(GameObject* pOwner) : 
	Component::Component(pOwner),
	m_pBreathSpriteRight1{ std::make_shared<SpriteSheet>("FygarFireRight1.png", 1, 1) },
	m_pBreathSpriteRight2{ std::make_shared<SpriteSheet>("FygarFireRight2.png", 1, 1) },
	m_pBreathSpriteRight3{ std::make_shared<SpriteSheet>("FygarFireRight3.png", 1, 1) },
	m_pBreathSpriteLeft1{ std::make_shared<SpriteSheet>("FygarFireLeft1.png", 1, 1) },
	m_pBreathSpriteLeft2{ std::make_shared<SpriteSheet>("FygarFireLeft2.png", 1, 1) },
	m_pBreathSpriteLeft3{ std::make_shared<SpriteSheet>("FygarFireLeft3.png", 1, 1) }
{
	auto spriteAnimator = std::make_unique<SpriteAnimatorComponent>(pOwner);
	spriteAnimator->AddSpriteSheet(m_pBreathSpriteRight3);
	spriteAnimator->m_ShouldRender = false;
	m_pSpriteAnimator = spriteAnimator.get();
	m_Width = spriteAnimator->GetSize().x;
	pOwner->AddComponent(std::move(spriteAnimator));
}

void dae::FygarBreathComponent::Update(const double deltaTime)
{
	if (m_Active)
	{
		m_FrameTime += static_cast<float>(deltaTime);
		if (m_FrameTime > m_FrameDuration)
		{
			++m_CurrentFrame;
			if (m_CurrentFrame >= m_MaxFrames)
			{
				m_CurrentFrame = 0;
			}
			SetNewFrame(m_CurrentFrame);
		}
	}
}

void dae::FygarBreathComponent::Toggle(const bool active, const bool facingRight)
{
	if (active)
	{
		m_Active = true;
		m_FacingRight = facingRight;
		m_pSpriteAnimator->m_ShouldRender = true;
	}

	else
	{
		m_Active = false;
		m_CurrentFrame = 0;
		m_FrameTime = 0;
		m_pSpriteAnimator->m_ShouldRender = false;
	}
}

void dae::FygarBreathComponent::SetLocalPosition(const glm::vec2 newPos)
{
	m_pOwner->SetLocalPosition(newPos);
}

void dae::FygarBreathComponent::SetNewFrame(const int newFrame)
{
	if (m_FacingRight)
	{
		switch (newFrame)
		{
		case 0:
			m_pSpriteAnimator->AddSpriteSheet(m_pBreathSpriteRight1);
			break;
		case 1:
			m_pSpriteAnimator->AddSpriteSheet(m_pBreathSpriteRight2);
			break;
		case 2:
			m_pSpriteAnimator->AddSpriteSheet(m_pBreathSpriteRight3);
			break;
		default:
			m_pSpriteAnimator->AddSpriteSheet(m_pBreathSpriteRight1);
		}
		m_pOwner->GetCollider()->UpdateColliderSize(m_pSpriteAnimator->GetSize());
	}
	else
	{
		switch (newFrame)
		{
		case 0:
			m_pSpriteAnimator->AddSpriteSheet(m_pBreathSpriteLeft1);
			break;
		case 1:
			m_pSpriteAnimator->AddSpriteSheet(m_pBreathSpriteLeft2);
			break;
		case 2:
			m_pSpriteAnimator->AddSpriteSheet(m_pBreathSpriteLeft3);
			break;
		default:
			m_pSpriteAnimator->AddSpriteSheet(m_pBreathSpriteLeft1);
		}
		m_pOwner->SetLocalPosition(-m_pSpriteAnimator->GetSize().x, 0);
		m_pOwner->GetCollider()->UpdateColliderSize(m_pSpriteAnimator->GetSize());
	}
}
