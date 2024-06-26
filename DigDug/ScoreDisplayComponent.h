#ifndef SCOREDISPLAYCOMPONENT
#define SCOREDISPLAYCOMPONENT
#include "../Minigin/Component.h"

namespace dae
{
	class TextComponent;
	class ScoreDisplayComponent :
		public Component, public EventListener
	{
	public:
		void Update(const double deltaTime) override;

		ScoreDisplayComponent(GameObject* pOwner, const std::string& playerName);
		virtual ~ScoreDisplayComponent();
		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

		virtual void HandleEvent(const Event& event) override;
		const int GetScore() const { return m_Score; }
		const std::string& GetPlayerName() const { return m_PlayerName; }
	private:
		int m_Score{ 0 };
		dae::TextComponent* m_pTextComponent;
		bool m_NeedsUpdate{ true };
		const std::string m_PlayerName;
	};
}

#endif