#include "SpriteAnimatorComponent.h"

dae::SpriteAnimatorComponent::SpriteAnimatorComponent(GameObject* owner) : 
	Component::Component(owner)
{
}

dae::SpriteAnimatorComponent::~SpriteAnimatorComponent()
{
	m_SpriteSheet.reset();
}

void dae::SpriteAnimatorComponent::Update(const double elapsedSec)
{
	m_SpriteTimer += elapsedSec;

	if (m_Looping == false && m_CurrentFrame == m_EndFrame)
	{
		m_CurrentFrame = m_EndFrame;
		m_LoopFinished = true;
	}

	if (m_SpriteTimer > m_FrameTime)
	{
		if (m_CurrentFrame != m_EndFrame)
		{
			++m_CurrentFrame;
		}
		else if (m_CurrentFrame >= m_EndFrame && m_Looping)
		{
			m_CurrentFrame = 0;
		}
		m_SpriteTimer -= m_FrameTime;
	}
}

void dae::SpriteAnimatorComponent::FixedUpdate(const double)
{
}

void dae::SpriteAnimatorComponent::AddSpriteSheet(const std::string& fileName, const int rows, const int columns)
{
	auto texture = ResourceManager::GetInstance().LoadTexture(fileName);
	m_SpriteSheet = std::make_shared<SpriteSheet>(std::move(texture), rows, columns);

	m_Width = static_cast<float>(m_SpriteSheet->GetWidth() / m_SpriteSheet->m_Columns);
	m_Height = static_cast<float>(m_SpriteSheet->GetHeight() / m_SpriteSheet->m_Rows);

	m_Looping = true;
	m_LoopFinished = false;
}

void dae::SpriteAnimatorComponent::AddSpriteSheet(std::shared_ptr<SpriteSheet> spriteSheet)
{
	if (m_SpriteSheet.get() != nullptr)
	{
		m_SpriteSheet.reset();
	}

	m_SpriteSheet = spriteSheet;
	m_Width = static_cast<float>(m_SpriteSheet->GetWidth() / m_SpriteSheet->m_Columns);
	m_Height = static_cast<float>(m_SpriteSheet->GetHeight() / m_SpriteSheet->m_Rows);
	m_Looping = true;
	m_LoopFinished = false;
}

void dae::SpriteAnimatorComponent::Render() const
{
	if (m_ShouldRender)
	{
		SDL_Rect srcRect{};
		srcRect.w = m_SpriteSheet->GetWidth() / m_SpriteSheet->m_Columns;
		srcRect.h = m_SpriteSheet->GetHeight() / m_SpriteSheet->m_Rows;
		srcRect.x = m_CurrentFrame % m_SpriteSheet->m_Columns * srcRect.w;
		srcRect.y = 0;

		const auto& pos = m_pOwner->GetWorldPosition();

		SDL_Rect destRect{};
		destRect.x = static_cast<int>(pos.x);
		destRect.y = static_cast<int>(pos.y);
		destRect.w = srcRect.w;
		destRect.h = srcRect.h;

		Renderer::GetInstance().RenderTexture(m_SpriteSheet->GetTexture(), &srcRect, &destRect);
	}
}

const bool dae::SpriteAnimatorComponent::RenderOnce()
{
	m_Looping = false;

	return m_LoopFinished;
}



const glm::vec2 dae::SpriteAnimatorComponent::GetSize() const
{
	const glm::vec2 result{ m_Width, m_Height };

	return result;
}
