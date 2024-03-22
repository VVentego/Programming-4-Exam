#ifndef MINIGIN
#define MINIGIN

#include <string>
#include <functional>
#include "GameObject.h"
#include "TextComponent.h"
#include "FpsCounterComponent.h"
#include "RotatorComponent.h"
#include "TextureComponent.h"
#include "PlayerController.h"
#include "ScoreDisplayComponent.h"
#include "LivesDisplayComponent.h"

const int gWindowWidth{ 640 };
const int gWindowHeight{ 480 };

__declspec(selectany) CSteamAchievements* g_SteamAchievements {};
__declspec(selectany) Achievement_t g_Achievements[] =
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
};

namespace dae
{
	struct Vector2
	{
		float x{};
		float y{};
	};

	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);



		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		const int GetMonitorRefreshRate();
		const int m_RefreshRate{ 60 };
	};
}
#endif // !MINIGIN