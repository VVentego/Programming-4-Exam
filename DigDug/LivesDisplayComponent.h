#ifndef LIVESDISPLAY
#define LIVESDISPLAY
#include "../Minigin/Component.h"

namespace dae
{
	class TextComponent;
    class LivesDisplayComponent final:
        public Component, public EventListener
    {
	public:
		void Update(const double deltaTime) override;

		LivesDisplayComponent(GameObject* pOwner, const std::string& playerName);
		~LivesDisplayComponent();
		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

		virtual void HandleEvent(const Event& event) override;
		const int GetLives() const { return m_Lives; }
	private:
		int m_Lives{ 3 };
		dae::TextComponent* m_pTextComponent;
		bool m_NeedsUpdate{ true };
		const std::string m_PlayerName;
    };
}
#endif // !LIVESDISPLAY