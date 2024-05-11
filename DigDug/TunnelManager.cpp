#include "TunnelManager.h"
#include "TunnelTextureComponent.h"

void dae::TunnelManager::Init(const std::string& tunnelFileName, std::vector <glm::vec2> tunnels)
{
	m_TunnelManagerObject = new GameObject;
	auto tunnelComponent = std::make_unique<TunnelComponent>(m_TunnelManagerObject, tunnelFileName, tunnels);
	m_TunnelManagerObject->AddComponent(std::move(tunnelComponent));
}

bool dae::TunnelManager::InTunnel(const glm::vec2 position)
{
	return m_TunnelManagerObject->GetComponent<TunnelComponent>()->InTunnel(position);
}

dae::TunnelManager::TunnelComponent::TunnelComponent(GameObject* pOwner, const std::string& tunnelFileName, std::vector<glm::vec2> tunnels) :
	Component::Component(pOwner), m_Tunnels{ std::move(tunnels) }
{
	auto textureComponent = std::make_unique<TunnelTextureComponent>(pOwner, &m_Tunnels);
	m_pTextureComponent = textureComponent.get();
	m_pTextureComponent->SetTexture(tunnelFileName);
	m_TunnelLength = m_pTextureComponent->GetSize().x;
	pOwner->AddComponent(std::move(textureComponent));
}

bool dae::TunnelManager::TunnelComponent::InTunnel(const glm::vec2 positionToCheck)
{
	for (auto& tunnelRect : m_Tunnels)
	{
		// Check if position is inside tunnel.
		if (positionToCheck.x >= tunnelRect.x && positionToCheck.y >= tunnelRect.y &&
			positionToCheck.x < tunnelRect.x + m_TunnelLength && positionToCheck.y < tunnelRect.y + m_TunnelLength)
		{
			// If all conditions are true, position is inside this tunnel.
			return true;
		}
	}
	// If position is not inside any tunnels, return false.
	return false;
}

void dae::TunnelManager::DigTunnel(const glm::vec2 position)
{
	m_TunnelManagerObject->GetComponent<TunnelComponent>()->DigTunnel(position);
}

glm::vec2 dae::TunnelManager::TunnelComponent::FindNearestTunnel(const glm::vec2 position) const
{
	if (m_Tunnels.empty())
	{
		return glm::vec2();
	}

	auto nearestTunnel = std::min_element(m_Tunnels.begin(), m_Tunnels.end(),
		[position](const glm::vec2& tunnelPos1, const glm::vec2& tunnelPos2)
		{
			float dist1 = glm::distance(position, tunnelPos1);
			float dist2 = glm::distance(position, tunnelPos2);
			return dist1 < dist2;
		});

	return *nearestTunnel;
}

void dae::TunnelManager::TunnelComponent::DigTunnel(const glm::vec2 position)
{
	m_Tunnels.emplace_back(position);
}

void dae::TunnelManager::TunnelComponent::Update(const double)
{
}
