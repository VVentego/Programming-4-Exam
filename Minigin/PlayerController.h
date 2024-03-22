#ifndef PLAYERCONTROLLER
#define PLAYERCONTROLLER

#include "Component.h"
namespace dae
{
    class PlayerController :
        public Component
    {
    public:
        PlayerController(GameObject* pOwner, const std::string& playerName, bool usingController);
        virtual ~PlayerController() = default;
        PlayerController (const PlayerController& other) = delete;
        PlayerController(PlayerController&& other) = delete;
        PlayerController& operator=(const PlayerController& other) = delete;
        PlayerController& operator=(PlayerController&& other) = delete;

        void Update(const double deltaTime) override;
        void HandleInput();

        void Move(const float x, const float y);
        void OnKillEnemy();
        void OnPlayerDeath();

        const std::string m_PlayerName;
    private:
        const float m_MoveSpeed{ 100.f };
        double m_deltaTime{};
        bool m_UsingController{};
    };
}
#endif // !PLAYERCONTROLLER
