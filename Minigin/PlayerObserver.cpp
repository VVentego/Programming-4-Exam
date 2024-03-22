#include "PlayerObserver.h"
#include "Component.h"

void dae::PlayerObserver::OnNotify(const Component* notifier, Event event)
{
	auto it = std::find(m_pSubjects.begin(), m_pSubjects.end(), notifier);
	if (it == m_pSubjects.end()) return;

	switch (event)
	{
	case Event::HighScore:

		break;
	case Event::Death:
		break;
	}
}

void dae::PlayerObserver::AddSubject(Component* subject)
{
	m_pSubjects.emplace_back(subject);
}

void dae::PlayerObserver::RemoveSubject(Component* subject)
{
	m_pSubjects.erase(remove(m_pSubjects.begin(), m_pSubjects.end(), subject), m_pSubjects.end());
}
