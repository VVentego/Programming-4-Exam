#include <SDL.h>
#include "Texture2D.h"

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 dae::Texture2D::GetSize() const
{
	SDL_Rect dst;
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

dae::SpriteSheet::SpriteSheet(SDL_Texture* texture, const int rows, const int columns) :
	m_Rows{ rows }, m_Columns{ columns }
{
	m_SpriteSheet = std::make_unique<Texture2D>(texture);
}

SDL_Texture* dae::SpriteSheet::GetSDLTexture() const
{
	return m_SpriteSheet->GetSDLTexture();
}
