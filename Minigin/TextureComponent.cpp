#include "TextureComponent.h"

dae::TextureComponent::TextureComponent(GameObject* pOwner) :
	dae::Component::Component(pOwner)
{

}

void dae::TextureComponent::Start()
{

}

void dae::TextureComponent::Render() const
{
	if (m_IsDestroyed) return;

	const auto& pos = m_pOwner->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_texture = texture;
}