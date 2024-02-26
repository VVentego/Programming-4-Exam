#include "Component.h"
#include <stdexcept>
#include "GameObject.h"

dae::Component::Component(GameObject* owner) : 
	m_pOwner{ owner }
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

void dae::Component::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::Component::Destroy()
{
	m_IsDestroyed = true;
}
