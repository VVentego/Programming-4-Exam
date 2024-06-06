#ifndef LEVELLOADER
#define LEVELLOADER
#include <lua.hpp>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <Scene.h>

struct LoadedPlayer {
    uint32_t id;
    glm::vec2 position;
    bool usesController;
};

class dae::Scene;

class LevelLoader {
public:
    LevelLoader();
    ~LevelLoader();

    bool LoadLevel(const std::string& levelFile);

    std::string GetBackground() const;
    std::vector<LoadedPlayer> GetPlayers() const;
    std::vector<glm::vec2> GetPookas() const;
    std::vector<glm::vec2> GetFygars() const;
    glm::vec2 GetFygarPlayer() const;
    std::vector<glm::vec2> GetTunnels() const;
    std::vector<glm::vec2> GetRocks() const;

    void CreateBackground(dae::Scene& scene) const;

    void CreateEntities(dae::Scene& scene);

    void CreateUI(dae::Scene& scene);

private:
    lua_State* L{};
    std::string m_Background{};
    std::vector<LoadedPlayer> m_Players;
    std::vector<glm::vec2> m_Pookas;
    std::vector<glm::vec2> m_Fygars;
    glm::vec2 m_FygarPlayer{ 0, 0 };
    std::vector<glm::vec2> m_Tunnels;
    std::vector<glm::vec2> m_Rocks;

    void LoadBackground();
    void LoadPlayers();
    void LoadPookas();
    void LoadFygars();
    void LoadFygarPlayer();
    void LoadTunnels();
    void LoadRocks();
};
#endif // !LEVELLOADER

