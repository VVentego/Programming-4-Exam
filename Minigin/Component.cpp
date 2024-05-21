#include "Component.h"
#include <stdexcept>
#include "GameObject.h"

dae::Component::Component(GameObject* owner) : 
	m_pOwner{ owner }
{
}

dae::Component::~Component() 
{
}

void dae::Component::NotifyObserver(Event event)
{
	EventObserver::GetInstance().Notify(event);
}

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
