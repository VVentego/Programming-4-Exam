#include "Component.h"
#include <stdexcept>
#include "GameObject.h"

dae::Component::Component(GameObject* owner) : 
	m_pOwner{ owner }, m_Position{ owner->GetWorldPosition() }
{
}

dae::Component::~Component() 
{
	RemoveAllObservers();
}

void dae::Component::NotifyObservers(Event event)
{
	for (PlayerObserver* observer : m_pObservers)
	{
		observer->OnNotify(this, event);
	}
}

void dae::Component::AddObserver(PlayerObserver* observer)
{
	observer->AddSubject(this);
	m_pObservers.emplace_back(observer);
}

void dae::Component::RemoveObserver(PlayerObserver* observer)
{
	observer->RemoveSubject(this);
	m_pObservers.erase(remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
}

void dae::Component::OnObserverDestroyed(PlayerObserver* observer)
{
	m_pObservers.erase(remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
}

void dae::Component::RemoveAllObservers()
{
	for (PlayerObserver* observer : m_pObservers)
	{
		observer->RemoveSubject(this);
		m_pObservers.erase(remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
	}
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
