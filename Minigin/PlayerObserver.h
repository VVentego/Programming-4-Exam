#ifndef PLAYEROBSERVER
#define PLAYEROBSERVER
#include <vector>
#include "CSteamAchievements.h"

namespace dae
{
	enum Event
	{
		HighScore,
		Death
	};

    class PlayerObserver
    {
		friend class Component;
    public:
        PlayerObserver() = default;
		virtual ~PlayerObserver() = default;
        PlayerObserver(const PlayerObserver& other) = delete;
        PlayerObserver(PlayerObserver&& other) = delete;
        PlayerObserver& operator=(const PlayerObserver& other) = delete;
        PlayerObserver& operator=(PlayerObserver&& other) = delete;

        virtual void OnNotify(const Component* notifier, Event event);
		virtual void AddSubject(Component* subject);
		virtual void RemoveSubject(Component* subject);

    private:
		int m_PlayerScore{};
		int m_PlayerLives{ 3 };

		std::vector<Component*> m_pSubjects;
    };
}

#endif // !PLAYEROBSERVER