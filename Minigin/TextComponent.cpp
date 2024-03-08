#include <stdexcept>
#include "TextComponent.h"
#include <SDL_ttf.h>

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, GameObject* pOwner)
	: Component::Component(pOwner), m_needsUpdate(true), m_text(text), m_font(std::move(font))
{
	m_pTextureComponent = std::make_unique<TextureComponent>(pOwner);
}

void dae::TextComponent::Update(const double)
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextureComponent->SetTexture(std::move(std::make_unique<Texture2D>(texture)));
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	m_pTextureComponent->Render();
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}