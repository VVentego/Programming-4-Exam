#include "FpsCounterComponent.h"

dae::FpsCounterComponent::FpsCounterComponent(std::shared_ptr<Font> font) :
	dae::TextComponent::TextComponent("60.0", font)
{

}

void dae::FpsCounterComponent::Update(const double deltaTime)
{
	const double fps{ 1 / deltaTime };

	SetText(std::to_string(fps));

	TextComponent::Update(deltaTime);
}

void dae::FpsCounterComponent::FixedUpdate(const double)
{

}

void dae::FpsCounterComponent::Render() const
{
	TextComponent::Render();
}

// This implementation uses the "dirty flag" pattern
void dae::FpsCounterComponent::SetText(const std::string& text)
{
	TextComponent::SetText(text);
}

void dae::FpsCounterComponent::SetPosition(const float x, const float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}