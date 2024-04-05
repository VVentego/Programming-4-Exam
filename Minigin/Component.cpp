#include "Component.h"
#include <stdexcept>
#include "GameObject.h"

dae::Component::Component(GameObject* owner) : 
	m_pOwner{ owner }
{
}

dae::Component::~Component() 
{
	RemoveAllObservers();
}

void dae::Component::NotifyObservers(Event event)
{
	for (std::weak_ptr<PlayerObserver> observer : m_pObservers)
	{
		if (!observer.expired())
		{
			observer.lock()->OnNotify(event);
		}

		else RemoveObserver(observer);
	}
}

void dae::Component::AddObserver(std::shared_ptr<PlayerObserver> observer)
{
	observer->AddSubject(this);
	m_pObservers.emplace_back(std::weak_ptr<PlayerObserver>(observer));
}

void dae::Component::RemoveObserver(std::weak_ptr<PlayerObserver> observer)
{
	const auto pos = std::find_if(m_pObservers.begin(), m_pObservers.end(), [observer](const std::weak_ptr<PlayerObserver>& otherPtr) {
		return otherPtr.lock().get() == observer.lock().get(); });

	if (pos != m_pObservers.end())
	{
		m_pObservers.erase(pos);
	}
}

void dae::Component::RemoveAllObservers()
{
	for (std::weak_ptr<PlayerObserver> observer : m_pObservers)
	{
		if (!observer.expired())
		{
			observer.lock()->RemoveSubject(this);
		}
	}
	m_pObservers.clear();
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
