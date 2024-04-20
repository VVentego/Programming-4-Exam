#include "TunnelManagerComponent.h"
#include "TunnelTextureComponent.h"

dae::TunnelManagerComponent::TunnelManagerComponent(GameObject* owner, const std::string& tunnelFileName, std::vector<Rectf> tunnels) :
	Component::Component(owner), m_Tunnels{ tunnels }
{
	auto textureComponent = std::make_unique<TunnelTextureComponent>(owner, &m_Tunnels);
	m_pTextureComponent = textureComponent.get();
	m_pTextureComponent->SetTexture(tunnelFileName);
	m_TunnelLength = m_pTextureComponent->GetSize().x;
	owner->AddComponent(std::move(textureComponent));
}

void dae::TunnelManagerComponent::Update(const double)
{

}

bool dae::TunnelManagerComponent::InTunnel(const glm::vec2 positionToCheck)
{
	for (auto& tunnelRect : m_Tunnels)
	{
		//Check if position is outside tunnel. Only return true if none of these are true.
		if (positionToCheck.x < tunnelRect.x)
		{
			continue;
		}
		if (positionToCheck.y < tunnelRect.y)
		{
			continue;
		}
		if (positionToCheck.x > tunnelRect.x + tunnelRect.w)
		{
			continue;
		}
		if (positionToCheck.y > tunnelRect.y + tunnelRect.h)
		{
			continue;
		}

		else
		{
			return true;
		}
	}

	return false;
}

void dae::TunnelManagerComponent::DigTunnel(const glm::vec2 position)
{
	Rectf newRect{};

	const float positionX{ position.x };
	const float positionY{ position.y };

	newRect = { positionX - m_TunnelLength / 2, positionY - m_TunnelLength / 2, m_TunnelLength, m_TunnelLength };

	m_Tunnels.push_back(newRect);
}
