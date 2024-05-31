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

std::string LevelLoader::GetBackground() const 
{
    return m_Background;
}

std::vector<LoadedPlayer> LevelLoader::GetPlayers() const
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

void LevelLoader::CreateBackground(dae::Scene& scene)
{
    auto go = std::make_unique<dae::GameObject>();

    go->AddComponent(std::make_unique<dae::TextureComponent>(go.get(), static_cast<float>(gWindowWidth), static_cast<float>(gWindowHeight)));
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
        digdug->SetWorldPosition(player.position.x, player.position.y);
        digdug->AddComponent(std::make_unique<dae::DigDugController>(digdug.get(), std::string("Player").append(std::to_string(player.id)), pump.get()));
        digdug->GetComponent<dae::DigDugController>()->SetStartPos(player.position);
        digdug->AddCollider(scene);

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
        pooka->SetWorldPosition(pookaPos.x, pookaPos.y);
        for (auto digdug : digdugs)
        {
            pooka->GetComponent<dae::PookaBehavior>()->AddPlayerToChase(digdug);
        }
        pooka->AddCollider(scene);
        scene.Add(std::move(pooka));
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

    float offset{ 5 };
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("60.0", font, go.get()));
    go->AddComponent(std::make_unique<dae::FpsCounterComponent>(go.get()));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 0, 0, 255 });
    go->SetWorldPosition(offset, offset);
    scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    font = std::move(resourceManager.LoadFont("Lingua.otf", 14));
    go->AddComponent(std::make_unique<dae::TextComponent>("Use WASD to move Dig Dug, Z and X to attack.", font, go.get()));
    go->SetWorldPosition(5, gWindowHeight - 75);
    scene.Add(std::move(go));

    //Score Display Event Handler
    go = std::make_unique<dae::GameObject>();
    font = std::move(resourceManager.LoadFont("Lingua.otf", 24));
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player0"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, gWindowHeight - 100);
    scene.Add(std::move(go));

    //Score Display Event Handler
    go = std::make_unique<dae::GameObject>();
    font = std::move(resourceManager.LoadFont("Lingua.otf", 24));
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, gWindowHeight - 150);
    scene.Add(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    font = std::move(resourceManager.LoadFont("Lingua.otf", 24));
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player0"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, gWindowHeight - 125);
    scene.Add(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    font = std::move(resourceManager.LoadFont("Lingua.otf", 24));
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, gWindowHeight - 175);
    scene.Add(std::move(go));
}