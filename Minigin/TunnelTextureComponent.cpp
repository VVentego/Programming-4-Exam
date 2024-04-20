#include "TunnelTextureComponent.h"

void dae::TunnelTextureComponent::Render() const
{
	if (m_IsDestroyed || !m_ShouldRender) return;
	if (m_pTunnels == nullptr) return;

	std::vector<Rectf>& tunnels = *m_pTunnels;

	for (Rectf& tunnel : tunnels)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, tunnel.x, tunnel.y, tunnel.w, tunnel.h);
	}
}

dae::TunnelTextureComponent::TunnelTextureComponent(GameObject* pOwner, std::vector<Rectf>* pTunnelVector) :
	TextureComponent::TextureComponent(pOwner), m_pTunnels{ pTunnelVector }
{
}