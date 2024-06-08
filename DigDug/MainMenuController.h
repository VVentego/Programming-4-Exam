#ifndef MAINMENU
#define MAINMENU
#include <Component.h>
#include <Player.h>
#include <chrono>

namespace dae
{
    using namespace std::chrono_literals;
    class MainMenuController :
        public Component, public Player
    {
    public:
        MainMenuController(GameObject* pOwner, const int windowWidth, const int windowHeight, Scene& scene);
        virtual ~MainMenuController();
        MainMenuController(const MainMenuController& other) = delete;
        MainMenuController(MainMenuController&& other) = delete;
        MainMenuController& operator=(const MainMenuController& other) = delete;
        MainMenuController& operator=(MainMenuController&& other) = delete;

        void Update(const double deltaTime) override;

    private:
        void HandleInput(Command* command) override;

        void MoveRight() override {};
        void MoveDown() override;
        void MoveLeft() override {};
        void MoveUp() override;
        void Shoot() override;
        void Mute() override;
        void Skip() override {};
        int m_SelectionIdx{};
        const int m_MaxOptions{ 2 };
        std::vector <glm::vec2> m_ButtonPositions;
        glm::vec2 m_PointerSize{};

        std::chrono::time_point<std::chrono::steady_clock> m_LastButtonPress{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> m_HoldButtonThreshold{ 0.1s };
        GameObject* m_Pointer{};
    };
}
#endif //MAINMENU