#include <stdexcept>
#include "TextObject.h"

dae::TextObject::TextObject(const std::string& text, std::shared_ptr<Font> font) 
	: m_text(text), m_font(std::move(font))
{
	m_TextComponent = std::make_shared<TextComponent>(m_text, m_font);
}

void dae::TextObject::Update(const double deltaTime)
{
	m_TextComponent->Update(deltaTime);
}

void dae::TextObject::Render() const
{
	m_TextComponent->Render();
}

// This implementation uses the "dirty flag" pattern
void dae::TextObject::SetText(const std::string& text)
{
	m_TextComponent->SetText(text);
}

void dae::TextObject::SetPosition(const float x, const float y)
{
	m_TextComponent->SetPosition(x, y);
}