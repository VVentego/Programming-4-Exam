#include "HighScoreHandler.h"

HighScoreHandler::HighScoreHandler(const std::string& fileName) :
    m_FileName{ fileName }
{
    m_RecordedScores.resize(m_MaxHighScores);
    std::fill(m_RecordedScores.begin(), m_RecordedScores.end(), HighScoreEntry{});

    ReadFromFile();
}

void HighScoreHandler::AddHighScore(const std::string& name, int score) {
    HighScoreEntry entry{};
    strncpy_s(entry.name.data(), entry.name.size(), name.c_str(), 3);
    entry.score = score;

        m_RecordedScores.push_back(entry);
        std::sort(m_RecordedScores.begin(), m_RecordedScores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b)
            {
                return a.score > b.score;
            });
        if (m_RecordedScores.size() > m_MaxHighScores)
        {
            m_RecordedScores.pop_back();
        }

    WriteToFile();
}

void HighScoreHandler::ReadFromFile()
{
    std::ifstream file(m_FileName, std::ios::binary);
    if (!file.is_open())
    {
        InitializeDefaultScores();
        WriteToFile();
        return;
    }
    int singlePlayerCount{};

    file.read(reinterpret_cast<char*>(&singlePlayerCount), sizeof(singlePlayerCount));
    m_RecordedScores.resize(singlePlayerCount);
    file.read(reinterpret_cast<char*>(m_RecordedScores.data()), singlePlayerCount * sizeof(HighScoreEntry));

    file.close();
}

void HighScoreHandler::WriteToFile() const {
    std::ofstream file(m_FileName, std::ios::binary);
    if (!file.is_open()) return;

    int singlePlayerCount = static_cast<int>(m_RecordedScores.size());
    file.write(reinterpret_cast<const char*>(&singlePlayerCount), sizeof(singlePlayerCount));
    file.write(reinterpret_cast<const char*>(m_RecordedScores.data()), singlePlayerCount * sizeof(HighScoreEntry));

    file.close();
}

bool HighScoreHandler::IsNewHighScore(int score) const {
    const auto& scores = m_RecordedScores;
    if (scores.size() < m_MaxHighScores) 
    {
        return true;
    }
    return score > scores.back().score;
}

void HighScoreHandler::InitializeDefaultScores() {
    m_RecordedScores.clear();
    for (size_t i{}; i < m_MaxHighScores; ++i) {
        HighScoreEntry defaultEntry;
        strncpy_s(defaultEntry.name.data(), defaultEntry.name.size(), "TCL", 3);
        defaultEntry.score = 100 * static_cast<int>(i);
        m_RecordedScores.push_back(defaultEntry);
    }
}