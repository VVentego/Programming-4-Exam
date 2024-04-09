#include "PlayerObserver.h"
#include "Component.h"
#include "EventHandler.h"

void dae::PlayerObserver::OnNotify(const Event& event)
{
	BroadcastToListeners(event);
}

void dae::PlayerObserver::AddSubject(Component* subject)
{
	m_pSubjects.emplace_back(subject);
}

void dae::PlayerObserver::RemoveSubject(Component* subject)
{
	m_pSubjects.erase(remove(m_pSubjects.begin(), m_pSubjects.end(), subject), m_pSubjects.end());
}

void dae::PlayerObserver::BroadcastToListeners(const Event& event)
{
	for (EventListener* handler : m_pListeners)
	{
		handler->HandleEvent(event);
	}
}