#include "ScoreDisplayComponent.h"

dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* pOwner) :
	Component::Component(pOwner)
{
	m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
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