#include "FpsCounterComponent.h"
#include "GameObject.h"

dae::FpsCounterComponent::FpsCounterComponent(GameObject* pOwner) :
	Component::Component(pOwner)
{
	m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
}

void dae::FpsCounterComponent::Update(const double deltaTime)
{
	Component::Update(deltaTime);
	m_Fps = 1 / deltaTime;

	if (m_pTextComponent != nullptr)
		m_pTextComponent->SetText(std::to_string(m_Fps));
}