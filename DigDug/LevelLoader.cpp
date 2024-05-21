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
    LoadPlayerPosition();
    LoadPookas();
    LoadFygars();
    LoadTunnels();

    return true;
}

void LevelLoader::LoadBackground() {
    lua_getglobal(L, "background");
    if (lua_isstring(L, -1)) {
        background = lua_tostring(L, -1);
    }
    lua_pop(L, 1);
}

void LevelLoader::LoadPlayerPosition() {
    lua_getglobal(L, "player");
    if (lua_istable(L, -1)) {
        lua_getfield(L, -1, "x");
        playerPosition.x = static_cast<float>(lua_tointeger(L, -1));
        lua_pop(L, 1);

        lua_getfield(L, -1, "y");
        playerPosition.y = static_cast<float>(lua_tointeger(L, -1));
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}

void LevelLoader::LoadPookas() {
    lua_getglobal(L, "pookas");
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        while (lua_next(L, -2)) {
            if (lua_istable(L, -1)) {
                glm::vec2 pos;
                lua_getfield(L, -1, "x");
                pos.x = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                lua_getfield(L, -1, "y");
                pos.y = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                pookas.push_back(pos);
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
                glm::vec2 pos;
                lua_getfield(L, -1, "x");
                pos.x = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                lua_getfield(L, -1, "y");
                pos.y = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                fygars.push_back(pos);
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
                glm::vec2 pos;
                lua_getfield(L, -1, "x");
                pos.x = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                lua_getfield(L, -1, "y");
                pos.y = static_cast<float>(lua_tointeger(L, -1));
                lua_pop(L, 1);

                tunnels.push_back(pos);
            }
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);
}

std::string LevelLoader::GetBackground() const {
    return background;
}

glm::vec2 LevelLoader::GetPlayerPosition() const {
    return playerPosition;
}

std::vector<glm::vec2> LevelLoader::GetPookas() const {
    return pookas;
}

std::vector<glm::vec2> LevelLoader::GetFygars() const {
    return fygars;
}

std::vector<glm::vec2> LevelLoader::GetTunnels() const {
    return tunnels;
}