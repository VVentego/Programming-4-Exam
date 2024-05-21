// LevelLoader.cpp
#include "LevelLoader.h"

LevelLoader::LevelLoader() {
    L = luaL_newstate();
    luaL_openlibs(L);
}

LevelLoader::~LevelLoader() {
    lua_close(L);
}

bool LevelLoader::LoadLevel(const std::string& levelFile) {
    if (luaL_loadfile(L, levelFile.c_str()) || lua_pcall(L, 0, 0, 0)) {
        return false;
    }

    LoadBackground();
    LoadPlayers();
    LoadPookas();
    LoadFygars();
    LoadTunnels();

    return true;
}

void LevelLoader::LoadBackground() {
    lua_getglobal(L, "background");
    if (lua_isstring(L, -1)) {
        m_Background = lua_tostring(L, -1);
    }
    lua_pop(L, 1);
}

void LevelLoader::LoadPlayers() {
    lua_getglobal(L, "players");
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        while (lua_next(L, -2)) {
            if (lua_istable(L, -1)) {
                Player player{};
                lua_getfield(L, -1, "id");
                player.id = static_cast<int>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                lua_getfield(L, -1, "x");
                player.position.x = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                lua_getfield(L, -1, "y");
                player.position.y = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                lua_getfield(L, -1, "usesController");
                player.usesController = lua_toboolean(L, -1);
                lua_pop(L, 1);

                m_Players.push_back(player);
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}

void LevelLoader::LoadPookas() {
    lua_getglobal(L, "pookas");
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        while (lua_next(L, -2)) {
            if (lua_istable(L, -1)) {
                glm::vec2 pos{};
                lua_getfield(L, -1, "x");
                pos.x = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                lua_getfield(L, -1, "y");
                pos.y = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                m_Pookas.push_back(pos);
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}

void LevelLoader::LoadFygars() {
    lua_getglobal(L, "fygars");
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        while (lua_next(L, -2)) {
            if (lua_istable(L, -1)) {
                glm::vec2 pos{};
                lua_getfield(L, -1, "x");
                pos.x = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                lua_getfield(L, -1, "y");
                pos.y = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                m_Fygars.push_back(pos);
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}

void LevelLoader::LoadTunnels() {
    lua_getglobal(L, "tunnels");
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        while (lua_next(L, -2)) {
            if (lua_istable(L, -1)) {
                glm::vec2 pos{};
                lua_getfield(L, -1, "x");
                pos.x = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                lua_getfield(L, -1, "y");
                pos.y = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                m_Tunnels.push_back(pos);
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}

std::string LevelLoader::GetBackground() const 
{
    return m_Background;
}

std::vector<Player> LevelLoader::GetPlayers() const
{
    return m_Players;
}


std::vector<glm::vec2> LevelLoader::GetPookas() const {
    return m_Pookas;
}

std::vector<glm::vec2> LevelLoader::GetFygars() const {
    return m_Fygars;
}

std::vector<glm::vec2> LevelLoader::GetTunnels() const {
    return m_Tunnels;
}
