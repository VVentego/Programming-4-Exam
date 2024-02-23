#include "TextureComponent.h"

void dae::TextureComponent::Start()
{

}

void dae::TextureComponent::Update(const double)
{
	
}

void dae::TextureComponent::FixedUpdate(const double)
{
}

void dae::TextureComponent::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetPosition(const float x, const float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}