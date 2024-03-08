#include "Component.h"
#include <stdexcept>

dae::Component::Component(GameObject* owner) : 
	m_pOwner{ owner }, m_Position{ owner->GetWorldPosition() }
{
}

dae::Component::~Component() = default;

void dae::Component::Start() {}

void dae::Component::Render() const
{
	if (m_IsDestroyed) return;
}

void dae::Component::Update(const double) 
{
	if (m_IsDestroyed) return;
}

void dae::Component::FixedUpdate(const double) 
{
	if (m_IsDestroyed) return;
}

void dae::Component::Destroy()
{
	m_IsDestroyed = true;
}
