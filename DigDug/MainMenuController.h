#ifndef MAINMENU
#define MAINMENU
#include <Component.h>
#include <Player.h>

namespace dae
{
    class MainMenuController :
        public Component, public Player
    {
    public:
        MainMenuController(GameObject* pOwner, const int windowWidth, const int windowHeight, Scene& scene);
        virtual ~MainMenuController() = default;
        MainMenuController(const MainMenuController& other) = delete;
        MainMenuController(MainMenuController&& other) = delete;
        MainMenuController& operator=(const MainMenuController& other) = delete;
        MainMenuController& operator=(MainMenuController&& other) = delete;

        void Update(const double deltaTime) override;

    private:
        void HandleInput(Command* command) override;

        void MoveRight()override {};
        void MoveDown() override;
        void MoveLeft() override {};
        void MoveUp() override;
        void Shoot() override;
        int m_SelectionIdx{};
        const int m_MaxOptions{ 3 };
    };
}
#endif //MAINMENU