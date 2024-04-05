#include <SDL.h>
#include "Texture2D.h"

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 dae::Texture2D::GetSize() const
{
	SDL_Rect dst{};
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_texture = texture;
}

dae::SpriteSheet::SpriteSheet(std::unique_ptr<Texture2D> texture, const int rows, const int columns) :
	m_Rows{ rows }, m_Columns{ columns }
{
	m_SpriteSheet = std::move(texture);
}

dae::SpriteSheet::SpriteSheet(SpriteSheet* spriteSheet) :
	m_Rows{ spriteSheet->m_Rows }, m_Columns{ spriteSheet->m_Columns }
{
	m_SpriteSheet = std::make_shared<Texture2D>(m_SpriteSheet->GetSDLTexture());
}

dae::Texture2D& dae::SpriteSheet::GetTexture() const
{
	return *m_SpriteSheet.get();
}
