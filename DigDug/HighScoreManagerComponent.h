#pragma once
#include <Component.h>
#include "HighScoreHandler.h"
#include <vector>
#include <chrono>


namespace dae
{
    using namespace std::chrono_literals;
    class LetterSelection
    {
    public:
        LetterSelection() = default;
        ~LetterSelection() = default;
        LetterSelection(const LetterSelection& other) = delete;
        LetterSelection(LetterSelection&& other) noexcept;
        LetterSelection& operator=(const LetterSelection& other) = delete;
        LetterSelection& operator=(LetterSelection&& other) noexcept;

        void SelectUp();
        void SelectDown();

        const char* GetChar() const { return &m_CurrentSelection; }
    private:
        const unsigned int m_SmallestLetter{ 65 };
        const unsigned int m_LargestLetter{ 90 };
        char m_CurrentSelection{ static_cast<char>(65) };
    };

    class TextureComponent;
    class TextComponent;
    class ScoreDisplayComponent;
    class HighScoreManagerComponent :
        public Component, public Player
    {
    public:
        HighScoreManagerComponent(GameObject* pOwner, Scene& scene, const glm::vec2 screenDimensions, std::vector<ScoreDisplayComponent*> persistentObjects);
        ~HighScoreManagerComponent();
        HighScoreManagerComponent(const HighScoreManagerComponent& other) = delete;
        HighScoreManagerComponent(HighScoreManagerComponent&& other) = delete;
        HighScoreManagerComponent& operator=(const HighScoreManagerComponent& other) = delete;
        HighScoreManagerComponent& operator=(HighScoreManagerComponent&& other) = delete;

        void Update(const double) override {};

    private:
        void HandleInput(Command* command) override;

        void MoveRight() override;
        void MoveDown() override;
        void MoveLeft() override;
        void MoveUp() override;
        void Shoot() override;
        void Mute() override;
        void Skip() override;
        int m_SelectionIdx{};
        const int m_MaxOptions{ 2 };
        std::vector<LetterSelection> m_Letters;
        HighScoreHandler m_HighScoreHandler;

        const float m_LetterSpacing{ 50.f };
        GameObject* m_SelectionHighlight{};
        std::vector<GameObject*> m_LetterDisplayObjects;
        std::vector<TextComponent*> m_LetterDisplays;
        std::vector<GameObject*> m_ScoreDisplays;
        bool m_AllowNameInput{};
        int m_PlayerScore{};

        std::chrono::time_point<std::chrono::steady_clock> m_LastButtonPress{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> m_HoldButtonThreshold{ 0.2s };
    };
}
