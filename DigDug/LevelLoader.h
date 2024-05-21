#ifndef LEVELLOADER
#define LEVELLOADER
#include <lua.hpp>
#include <string>
#include <glm/glm.hpp>
#include <vector>

class LevelLoader {
public:
    LevelLoader();
    ~LevelLoader();

    bool LoadLevel(const std::string& levelFile);

    std::string GetBackground() const;
    glm::vec2 GetPlayerPosition() const;
    std::vector<glm::vec2> GetPookas() const;
    std::vector<glm::vec2> GetFygars() const;
    std::vector<glm::vec2> GetTunnels() const;

private:
    lua_State* L{};
    std::string background{};
    glm::vec2 playerPosition{};
    std::vector<glm::vec2> pookas;
    std::vector<glm::vec2> fygars;
    std::vector<glm::vec2> tunnels;

    void LoadBackground();
    void LoadPlayerPosition();
    void LoadPookas();
    void LoadFygars();
    void LoadTunnels();
};
#endif // !LEVELLOADER

