#ifndef SCOREDISPLAYCOMPONENT
#define SCOREDISPLAYCOMPONENT
#include "TextComponent.h"

namespace dae
{
	class ScoreDisplayComponent :
		public Component
	{
	public:
		void Update(const double deltaTime) override;
		void SetScore(const int score) { m_Score = score; m_NeedsUpdate = true; }

		ScoreDisplayComponent(GameObject* pOwner);
		virtual ~ScoreDisplayComponent() = default;
		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

	private:
		int m_Score{ 0 };
		dae::TextComponent* m_pTextComponent;
		bool m_NeedsUpdate{ true };
	};
}

#endif