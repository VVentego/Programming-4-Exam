#include "TunnelTextureComponent.h"

void dae::TunnelTextureComponent::Render() const
{
	if (m_IsDestroyed || !m_ShouldRender) return;
	if (m_pTunnels == nullptr) return;

	for (glm::vec2& tunnel : *m_pTunnels)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, tunnel.x, tunnel.y);
	}
}

dae::TunnelTextureComponent::TunnelTextureComponent(GameObject* pOwner, std::vector<glm::vec2>* pTunnelVector) :
	TextureComponent::TextureComponent(pOwner), m_pTunnels{ pTunnelVector }
{
}