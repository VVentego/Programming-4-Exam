// LevelLoader.cpp
#include "LevelLoader.h"
#include "ComponentsHeader.h"
#include <memory>
#include <Minigin.h>

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
    LoadRocks();

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
                LoadedPlayer player{};
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

void LevelLoader::LoadRocks()
{
    lua_getglobal(L, "rocks");
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

                m_Rocks.push_back(pos);
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

std::vector<LoadedPlayer> LevelLoader::GetPlayers() const
{
    return m_Players;
}


std::vector<glm::vec2> LevelLoader::GetPookas() const 
{
    return m_Pookas;
}

std::vector<glm::vec2> LevelLoader::GetFygars() const 
{
    return m_Fygars;
}

std::vector<glm::vec2> LevelLoader::GetTunnels() const 
{
    return m_Tunnels;
}

std::vector<glm::vec2> LevelLoader::GetRocks() const
{
    return m_Rocks;
}

void LevelLoader::CreateBackground(dae::Scene& scene) const
{
    auto go = std::make_unique<dae::GameObject>();

    go->AddComponent(std::make_unique<dae::TextureComponent>(go.get(), static_cast<float>(224), static_cast<float>(272)));
    go->GetComponent<dae::TextureComponent>()->SetTexture(m_Background);
    scene.Add(std::move(go));
}

void LevelLoader::CreateEntities(dae::Scene& scene)
{
    std::vector<dae::GameObject*> digdugs;

    for (auto& player : m_Players)
    {
        //Allow only two players
        if (player.id > 1)
        {
            return;
        }
        auto pump = std::make_unique<dae::GameObject>();

        pump->AddComponent(std::make_unique<dae::PumpBehaviorComponent>(pump.get(), 0));
        pump->AddCollider(scene);

        auto digdug = std::make_unique<dae::GameObject>();
        digdug->SetWorldPosition(player.position);
        digdug->AddComponent(std::make_unique<dae::DigDugController>(digdug.get(), std::string("Player").append(std::to_string(player.id)), pump.get()));
        digdug->GetComponent<dae::DigDugController>()->SetStartPos(player.position);
        digdug->AddCollider(scene);
        digdug->SnapToGrid();

        if (player.id == 0)
        {
            ServiceLocator::GetInputManager().AddPlayer1(*digdug->GetComponent<dae::DigDugController>());
        }
        else if (player.id == 1)
        {
            ServiceLocator::GetInputManager().AddPlayer2(*digdug->GetComponent<dae::DigDugController>());
        }
        digdugs.push_back(digdug.get());

        scene.Add(std::move(digdug));
        scene.Add(std::move(pump));
    }

    for (auto& pookaPos : m_Pookas)
    {
        auto pooka = std::make_unique<dae::GameObject>();
        pooka->AddComponent(std::make_unique<dae::PookaBehavior>(pooka.get()));
        pooka->SetWorldPosition(pookaPos);
        pooka->SnapToGrid();
        for (auto digdug : digdugs)
        {
            pooka->GetComponent<dae::PookaBehavior>()->AddPlayerToChase(digdug);
        }
        pooka->AddCollider(scene);
        scene.Add(std::move(pooka));
    }

    for (auto& fygarPos : m_Fygars)
    {
        auto fireBreath = std::make_unique<dae::GameObject>();
        fireBreath->AddComponent(std::make_unique<dae::FygarBreathComponent>(fireBreath.get()));

        auto fygar = std::make_unique<dae::GameObject>();
        fygar->AddComponent(std::make_unique<dae::FygarBehavior>(fygar.get(), fireBreath->GetComponent<dae::FygarBreathComponent>()));
        fygar->SetWorldPosition(fygarPos);
        fygar->SnapToGrid();
        fireBreath->SetParent(fygar.get(), false);
        for (auto digdug : digdugs)
        {
            fygar->GetComponent<dae::FygarBehavior>()->AddPlayerToChase(digdug);
        }
        fygar->AddCollider(scene);
        fireBreath->AddCollider(scene);
        scene.Add(std::move(fygar));
        scene.Add(std::move(fireBreath));
    }

    for (auto& rockPos : m_Rocks)
    {
        auto rock = std::make_unique<dae::GameObject>();
        rock->AddComponent(std::make_unique<dae::RockBehavior>(rock.get()));
        rock->SetWorldPosition(rockPos.x, rockPos.y);
        rock->SnapToGrid();
        for (auto digdug : digdugs)
        {
            rock->GetComponent<dae::RockBehavior>()->AddPlayer(digdug);
        }
        rock->AddCollider(scene);
        scene.Add(std::move(rock));
    }
}


void LevelLoader::CreateUI(dae::Scene& scene)
{
    auto& resourceManager = dae::ResourceManager::GetInstance();
    auto go = std::make_unique<dae::GameObject>();

    go->AddComponent(std::make_unique<dae::TextureComponent>(go.get()));
    go->GetComponent<dae::TextureComponent>()->SetTexture("logo.tga");
    go->SetWorldPosition(216, gWindowHeight - 180);
    scene.Add(std::move(go));

    std::shared_ptr<dae::Font> font = std::move(resourceManager.LoadFont("Lingua.otf", 36));
}