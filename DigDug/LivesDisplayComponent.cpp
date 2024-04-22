#include "LivesDisplayComponent.h"
#include "../Minigin/TextComponent.h"
#include <iostream>
dae::LivesDisplayComponent::LivesDisplayComponent(GameObject* pOwner, const std::string& playerName) :
	Component::Component(pOwner), m_PlayerName{ playerName }
{
	m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
}

void dae::LivesDisplayComponent::HandleEvent(const Event& event)
{
	if (event.type != EventType::PLAYER_DIED)
	{
		return;
	}
	if (event.stringValue == m_PlayerName)
	{
		--m_Lives;
		m_NeedsUpdate = true;
	}
}

void dae::LivesDisplayComponent::Update(const double deltaTime)
{
	Component::Update(deltaTime);

	if (m_pTextComponent != nullptr && m_NeedsUpdate)
	{
		std::string text = "# Lives: " + std::to_string(m_Lives);

		m_pTextComponent->SetText(text);
		m_NeedsUpdate = false;
	}
}