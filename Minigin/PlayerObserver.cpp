#include "PlayerObserver.h"
#include "Component.h"
#include "EventHandler.h"

void dae::PlayerObserver::OnNotify(const Event& event)
{
	BroadcastToHandlers(event);

	if (event.m_type == EventType::SCORE_INCREASED)
	{
		m_TotalScore += event.m_args[0].intValue;
		if (m_TotalScore >= m_WinnerScore)
		{
			UnlockAchievement();
		}
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

void dae::PlayerObserver::UnlockAchievement()
{
	if (m_SteamAchievements)
		m_SteamAchievements->SetAchievement("ACH_WIN_100_GAMES");
}

void dae::PlayerObserver::BroadcastToHandlers(const Event& event)
{
	for (EventHandler* handler : m_pEventHandlers)
	{
		handler->HandleEvent(event);
	}
}

void dae::PlayerObserver::SetSteamAchievementsHandler(CSteamAchievements* steamAchivements)
{
	m_SteamAchievements = steamAchivements;
}