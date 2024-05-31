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
    std::vector<glm::vec2> GetTunnels() const;

    void CreateBackground(dae::Scene& scene);

    void CreateEntities(dae::Scene& scene);

    void CreateUI(dae::Scene& scene);

private:
    lua_State* L{};
    std::string m_Background{};
    std::vector<LoadedPlayer> m_Players;
    std::vector<glm::vec2> m_Pookas;
    std::vector<glm::vec2> m_Fygars;
    std::vector<glm::vec2> m_Tunnels;

    void LoadBackground();
    void LoadPlayers();
    void LoadPookas();
    void LoadFygars();
    void LoadTunnels();
};
#endif // !LEVELLOADER

