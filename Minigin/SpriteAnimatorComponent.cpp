#include "SpriteAnimatorComponent.h"

dae::SpriteAnimatorComponent::SpriteAnimatorComponent(GameObject* owner) : 
	Component::Component(owner)
{
}

void dae::SpriteAnimatorComponent::Update(const double elapsedSec)
{
	m_SpriteTimer += elapsedSec;

	if (m_Looping == false && m_CurrentFrame == m_EndFrame) m_CurrentFrame = m_EndFrame;

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

//void dae::SpriteAnimatorComponent::FlipSprite(const bool left) const
//{
//	if (left == true)
//	{
//		glPushMatrix();
//		glScalef(-1, 1, 1);
//		glPopMatrix();
//	}
//
//	else if (left == false)
//	{
//		glPushMatrix();
//		glScalef(1, 1, 1);
//		glPopMatrix();
//	}
//}

void dae::SpriteAnimatorComponent::AddSpriteSheet(const std::string& fileName, const int rows, const int columns)
{
	auto texture = ResourceManager::GetInstance().LoadTexture(fileName);
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(std::move(texture), rows, columns);

	m_SpriteSheets.emplace_back(std::move(spriteSheet));
}

void dae::SpriteAnimatorComponent::AddSpriteSheet(SpriteSheet* spriteSheet)
{
	m_SpriteSheets.emplace_back(std::make_shared<SpriteSheet>(spriteSheet));
}

void dae::SpriteAnimatorComponent::Render() const
{
	SDL_Rect srcRect{};
	srcRect.w = m_SpriteSheets[m_CurrentSpriteSheet]->GetWidth() / m_SpriteSheets[m_CurrentSpriteSheet]->m_Columns;
	srcRect.h = m_SpriteSheets[m_CurrentSpriteSheet]->GetHeight() / m_SpriteSheets[m_CurrentSpriteSheet]->m_Rows;
	srcRect.x = m_CurrentFrame % m_SpriteSheets[m_CurrentSpriteSheet]->m_Columns * srcRect.w;
	srcRect.y = 0;

	const auto& pos = m_pOwner->GetWorldPosition();

	SDL_Rect destRect{};
	destRect.x = static_cast<int>(pos.x);
	destRect.y = static_cast<int>(pos.y);
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	Renderer::GetInstance().RenderTexture(m_SpriteSheets[m_CurrentSpriteSheet]->GetTexture(), &srcRect, &destRect);

	//if (m_Left == true)
	//{
	//	glPushMatrix();
	//	glScalef(-1, 1, 1);

	//	m_SpriteSheets[m_CurrentSpriteSheet]->Draw(Rectf{ -destRect.left - destRect.width, destRect.bottom, destRect.width, destRect.height }, srcRect);
	//	glPopMatrix();
	//}

	//else if (m_Left == false)
	//{
	//	glPushMatrix();
	//	glScalef(1, 1, 1);
	//	m_SpriteSheets[m_CurrentSpriteSheet]->Draw(destRect, srcRect);
	//	glPopMatrix();
	//}
}

const glm::vec2 dae::SpriteAnimatorComponent::GetSize() const
{
	const glm::vec2 result{ m_Width, m_Height };

	return result;
}
