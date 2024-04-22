#include "ScoreDisplayComponent.h"
#include "../Minigin/TextComponent.h"
#include <iostream>
dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* pOwner, const std::string& playerName) :
	Component::Component(pOwner), m_PlayerName{ playerName }
{
	m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
}

void dae::ScoreDisplayComponent::HandleEvent(const Event& event)
{
	if (event.type != EventType::SCORE_INCREASED)
	{
		return;
	}
	if (event.stringValue == m_PlayerName)
	{
		m_Score += event.intValue;
		m_NeedsUpdate = true;
	}
}

void dae::ScoreDisplayComponent::Update(const double deltaTime)
{
	Component::Update(deltaTime);

	if (m_pTextComponent != nullptr && m_NeedsUpdate)
	{
		std::string text = "Score: " + std::to_string(m_Score);

		m_pTextComponent->SetText(text);
		m_NeedsUpdate = false;
	}
}