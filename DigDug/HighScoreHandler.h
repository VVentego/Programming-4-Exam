#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <string.h>

class HighScoreHandler
{
public:
    struct HighScoreEntry {
        std::array<char, 4> name{ "TCL" };
        int score{};
    };

    HighScoreHandler(const std::string& fileName);
    void AddHighScore(const std::string& name, int score);
    void ReadFromFile();
    void WriteToFile() const;
    bool IsNewHighScore(int score) const;
    std::vector<HighScoreEntry>& GetScores(){ return m_RecordedScores; }
private:
    void InitializeDefaultScores();
    std::string m_FileName;
    std::vector<HighScoreEntry> m_RecordedScores;
    const size_t m_MaxHighScores{ 5 };
};

