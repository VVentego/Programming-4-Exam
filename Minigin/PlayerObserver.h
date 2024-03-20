#ifndef PLAYEROBSERVER
#define PLAYEROBSERVER
#include <steam_api.h>
enum Event
{
	HighScore,
	Death
};

namespace dae
{
	class GameObject;
    class PlayerObserver
    {
    public:
        PlayerObserver() = default;
        virtual ~PlayerObserver() = default;
        PlayerObserver(const PlayerObserver& other) = delete;
        PlayerObserver(PlayerObserver&& other) = delete;
        PlayerObserver& operator=(const PlayerObserver& other) = delete;
        PlayerObserver& operator=(PlayerObserver&& other) = delete;

        virtual void OnNotify(const GameObject& player, Event event);
    private:
		int m_Player1Score{};
		int m_Player2Score{};
		int m_Player1Lives{ 3 };
		int m_Player2Lives{ 3 };
    };
}

#endif // !PLAYEROBSERVER
enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
struct Achievement_t
{
	int m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};

class CSteamAchievements
{
private:
	uint64 m_iAppID; // Our current AppID
	Achievement_t* m_pAchievements; // Achievements data
	int m_iNumAchievements; // The number of Achievements
	bool m_bInitialized{}; // Have we called Request stats and received the callback?

public:
	CSteamAchievements(Achievement_t* Achievements, int NumAchievements);
	~CSteamAchievements()= default;

	bool RequestStats();
	bool SetAchievement(const char* ID);

	STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
		m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
		m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
		UserAchievementStored_t, m_CallbackAchievementStored);
};
