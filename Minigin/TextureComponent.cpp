#include "TextureComponent.h"

dae::TextureComponent::TextureComponent(GameObject* pOwner) :
	dae::Component::Component(pOwner)
{

}

dae::TextureComponent::TextureComponent(GameObject* pOwner, const float width, const float height) :
	dae::Component::Component(pOwner), m_Width{ width }, m_Height{ height }
{

}

const glm::vec2 dae::TextureComponent::GetSize() const
{
	const auto textureSize{ m_texture->GetSize() };
	const glm::vec2 result{ textureSize.x, textureSize.y };

	return result;
}

void dae::TextureComponent::Start()
{

}

void dae::TextureComponent::Render() const
{
	if (m_IsDestroyed || !m_ShouldRender || !m_texture.get()) return;

	const auto& pos = m_pOwner->GetWorldPosition();
	
	if (m_Width != 0 && m_Height != 0)
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_Width, m_Height);
	
		else
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_texture.reset();
	m_texture = texture;
}