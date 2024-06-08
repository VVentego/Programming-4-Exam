#include "DigDugLevelState.h"
#include "LevelLoader.h"
#include <ServiceLocator.h>
#include <memory>
#include "TunnelManager.h"
#include <SceneManager.h>
#include <TextComponent.h>
#include "ScoreDisplayComponent.h"
#include <Minigin.h>
#include "LivesDisplayComponent.h"
#include "MainMenuController.h"
#include "HighScoreManagerComponent.h"
#include <chrono>

using namespace dae;
void SinglePlayerState1::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
	std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
	auto& newScene = dae::SceneManager::GetInstance().CreateScene("Level0");
	SceneManager& sceneManager = SceneManager::GetInstance();
	sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
	pLevelLoader->LoadLevel("../Data/Level0.lua");
#else
	pLevelLoader->LoadLevel("../Levels/Level0.lub");
#endif // _DEBUG
	pLevelLoader->CreateBackground(newScene);
    
    auto& resourceManager = dae::ResourceManager::GetInstance();

    //Score Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 12);
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, gWindowHeight / 2.f - 12);
    newScene.AddPersistentObject(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

	auto& tunnelManager = TunnelManager::GetInstance();

	tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

	newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}


void SinglePlayerState1::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (event.stringValue == "Player1")
        {
            --m_Player1Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::SKIP_LEVEL)
    {
        m_Exit = true;
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<SinglePlayerState2>();
        return;
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<SinglePlayerState2>();
            ServiceLocator::GetSoundManager().Play(7, 100);
            return;
        }
    }
}

std::unique_ptr<LevelState> SinglePlayerState1::OnExit(dae::Scene& scene)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= m_EndLevelDelay)
        {
            break;
        }
    }

    scene.RemoveAll();
    return std::move(m_NextState);
}

void SinglePlayerState2::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
    std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("Level1");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
    pLevelLoader->LoadLevel("../Data/Level1.lua");
#else
    pLevelLoader->LoadLevel("../Levels/Level1.lub");
#endif // _DEBUG
    pLevelLoader->CreateBackground(newScene);

    auto& resourceManager = dae::ResourceManager::GetInstance();

    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 12);
    //Lives Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

    auto& tunnelManager = TunnelManager::GetInstance();

    tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

    newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}

void SinglePlayerState2::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (event.stringValue == "Player1")
        {
            --m_Player1Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::SKIP_LEVEL)
    {
        m_Exit = true;
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<SinglePlayerState3>();
        return;
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<SinglePlayerState3>();
            ServiceLocator::GetSoundManager().Play(7, 100);
            return;
        }
    }
}

std::unique_ptr<LevelState> SinglePlayerState2::OnExit(dae::Scene& scene)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= m_EndLevelDelay)
        {
            break;
        }
    }

    scene.RemoveAll();
    return std::move(m_NextState);
}

void SinglePlayerState3::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
    std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("Level2");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
    pLevelLoader->LoadLevel("../Data/Level2.lua");
#else
    pLevelLoader->LoadLevel("../Levels/Level2.lub");
#endif // _DEBUG
    pLevelLoader->CreateBackground(newScene);

    auto& resourceManager = dae::ResourceManager::GetInstance();

    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 12);
    //Lives Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

    auto& tunnelManager = TunnelManager::GetInstance();

    tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

    newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}

void SinglePlayerState3::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (event.stringValue == "Player1")
        {
            --m_Player1Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::SKIP_LEVEL)
    {
        m_Exit = true;
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<EndScreenState>();
        return;
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<EndScreenState>();
            ServiceLocator::GetSoundManager().Play(7, 100);
            return;
        }
    }
}

std::unique_ptr<LevelState> SinglePlayerState3::OnExit(dae::Scene&)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= m_EndLevelDelay)
        {
            break;
        }
    }

    return std::move(m_NextState);
}

void CoopState1::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
    std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("CoopLevel0");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
    pLevelLoader->LoadLevel("../Data/Level0Coop.lua");
#else
    pLevelLoader->LoadLevel("../Levels/Level0Coop.lub");
#endif // _DEBUG
    pLevelLoader->CreateBackground(newScene);

    auto& resourceManager = dae::ResourceManager::GetInstance();

    //Score Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 12);
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, gWindowHeight / 2.f - 12);
    newScene.AddPersistentObject(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

    //Score Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player2"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5 + 108, gWindowHeight / 2.f - 12);
    newScene.AddPersistentObject(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player2"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5 + 128, 10);
    newScene.Add(std::move(go));

    auto& tunnelManager = TunnelManager::GetInstance();

    tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

    newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}


void CoopState1::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (event.stringValue == "Player1")
        {
            --m_Player1Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0 && m_Player2Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
        if (event.stringValue == "Player2")
        {
            --m_Player2Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0 && m_Player2Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::SKIP_LEVEL)
    {
        m_Exit = true;
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<CoopState2>();
        return;
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<CoopState2>();
            ServiceLocator::GetSoundManager().Play(7, 100);
            return;
        }
    }
}

std::unique_ptr<LevelState> CoopState1::OnExit(dae::Scene& scene)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= m_EndLevelDelay)
        {
            break;
        }
    }

    scene.RemoveAll();
    return std::move(m_NextState);
}

void CoopState2::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
    std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("Level1");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
    pLevelLoader->LoadLevel("../Data/Level1Coop.lua");
#else
    pLevelLoader->LoadLevel("../Levels/Level1Coop.lub");
#endif // _DEBUG
    pLevelLoader->CreateBackground(newScene);

    auto& resourceManager = dae::ResourceManager::GetInstance();

    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 12);
    //Lives Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player2"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5 + 128, 10);
    newScene.Add(std::move(go));

    auto& tunnelManager = TunnelManager::GetInstance();

    tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

    newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}

void CoopState2::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (event.stringValue == "Player1")
        {
            --m_Player1Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0 && m_Player2Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
        if (event.stringValue == "Player2")
        {
            --m_Player2Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0 && m_Player2Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::SKIP_LEVEL)
    {
        m_Exit = true;
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<CoopState3>();
        return;
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<CoopState3>();
            ServiceLocator::GetSoundManager().Play(7, 100);
            return;
        }
    }
}

std::unique_ptr<LevelState> CoopState2::OnExit(dae::Scene& scene)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= m_EndLevelDelay)
        {
            break;
        }
    }

    scene.RemoveAll();
    return std::move(m_NextState);
}

void CoopState3::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
    std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("Level2");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
    pLevelLoader->LoadLevel("../Data/Level2Coop.lua");
#else
    pLevelLoader->LoadLevel("../Levels/Level2Coop.lub");
#endif // _DEBUG
    pLevelLoader->CreateBackground(newScene);

    auto& resourceManager = dae::ResourceManager::GetInstance();

    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 12);
    //Lives Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player2"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5 + 128, 10);
    newScene.Add(std::move(go));

    auto& tunnelManager = TunnelManager::GetInstance();

    tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

    newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}

void CoopState3::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (m_Player1Lives <= 0 && m_Player2Lives <= 0)
        {
            --m_Player1Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
        if (m_Player1Lives <= 0 && m_Player2Lives <= 0)
        {
            --m_Player2Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player2Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }


    if (event.type == EventType::SKIP_LEVEL)
    {
        m_Exit = true;
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<EndScreenState>();
        return;
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<EndScreenState>();
            ServiceLocator::GetSoundManager().Play(7, 100);
            return;
        }
    }
}

std::unique_ptr<LevelState> CoopState3::OnExit(dae::Scene&)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= m_EndLevelDelay)
        {
            break;
        }
    }

    return std::move(m_NextState);
}

std::unique_ptr<LevelState> MainMenuState::OnExit(dae::Scene& scene)
{
    auto start = std::chrono::high_resolution_clock::now();
    float endLevelDelay{ 1.f };
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= endLevelDelay)
        {
            break;
        }
    }

    scene.RemoveAll();
    return std::move(m_NextState);
}

void MainMenuState::OnEnter(dae::Scene&)
{
    EventObserver::GetInstance().AddListener(this);
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("Level1");
    auto mainMenuController = std::make_unique<GameObject>();
    mainMenuController->AddComponent(std::make_unique<dae::MainMenuController>(mainMenuController.get(), gWindowWidth, gWindowHeight, newScene));
    newScene.Add(std::move(mainMenuController));

    auto title = std::make_unique<GameObject>();
    title->AddComponent(std::make_unique<TextureComponent>(title.get()));
    auto titleTexture = title->GetComponent<TextureComponent>();
    titleTexture->SetTexture("Title.png");
    title->SetWorldPosition(gWindowWidth / 4.f - titleTexture->GetSize().x / 2.f, 10);
    newScene.Add(std::move(title));
}

void MainMenuState::HandleEvent(const Event& event)
{
    if (event.type == EventType::LOAD_LEVEL)
    {
        if (event.stringValue == "Level0")
        {
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<SinglePlayerState1>();
            m_Exit = true;
        }
        if (event.stringValue == "Coop")
        {
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<CoopState1>();
            m_Exit = true;
        }
        if (event.stringValue == "versus")
        {
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<VersusPlayerState1>();
            m_Exit = true;
        }
    }
}

void VersusPlayerState1::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
    std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("versus1");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
    pLevelLoader->LoadLevel("../Data/Level0Versus.lua");
#else
    pLevelLoader->LoadLevel("../Levels/Level0Versus.lub");
#endif // _DEBUG
    pLevelLoader->CreateBackground(newScene);

    auto& resourceManager = dae::ResourceManager::GetInstance();

    //Score Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 12);
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, gWindowHeight / 2.f - 12);
    newScene.AddPersistentObject(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player2"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5 + 128, 10);
    newScene.Add(std::move(go));

    auto& tunnelManager = TunnelManager::GetInstance();

    tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

    newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}

std::unique_ptr<LevelState> VersusPlayerState1::OnExit(dae::Scene& scene)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= m_EndLevelDelay)
        {
            break;
        }
    }

    scene.RemoveAll();
    return std::move(m_NextState);
}

void VersusPlayerState1::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (event.stringValue == "Player1")
        {
            --m_Player1Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::SKIP_LEVEL)
    {
        m_Exit = true;
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<VersusPlayerState2>();
        return;
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<VersusPlayerState2>();
            ServiceLocator::GetSoundManager().Play(7, 100);
            return;
        }
    }
}


void VersusPlayerState2::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
    std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("versus2");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
    pLevelLoader->LoadLevel("../Data/Level1Versus.lua");
#else
    pLevelLoader->LoadLevel("../Levels/Level1Versus.lub");
#endif // _DEBUG
    pLevelLoader->CreateBackground(newScene);

    auto& resourceManager = dae::ResourceManager::GetInstance();

    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 12);
    //Lives Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player2"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5 + 128, 10);
    newScene.Add(std::move(go));

    auto& tunnelManager = TunnelManager::GetInstance();

    tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

    newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}

void VersusPlayerState2::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (event.stringValue == "Player1")
        {
            --m_Player1Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::SKIP_LEVEL)
    {
        m_Exit = true;
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<VersusPlayerState3>();
        return;
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<VersusPlayerState3>();
            ServiceLocator::GetSoundManager().Play(7, 100);
            return;
        }
    }
}

std::unique_ptr<LevelState> VersusPlayerState2::OnExit(dae::Scene& scene)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= m_EndLevelDelay)
        {
            break;
        }
    }

    scene.RemoveAll();
    return std::move(m_NextState);
}

void VersusPlayerState3::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
    std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("versus3");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
    pLevelLoader->LoadLevel("../Data/Level2Versus.lua");
#else
    pLevelLoader->LoadLevel("../Levels/Level2Versus.lub");
#endif // _DEBUG
    pLevelLoader->CreateBackground(newScene);

    auto& resourceManager = dae::ResourceManager::GetInstance();

    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 12);
    //Lives Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player2"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5 + 128, 10);
    newScene.Add(std::move(go));

    auto& tunnelManager = TunnelManager::GetInstance();

    tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

    newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}

void VersusPlayerState3::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (event.stringValue == "Player1")
        {
            --m_Player1Lives;
            ServiceLocator::GetSoundManager().Play(9, 100);
            if (m_Player1Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::SKIP_LEVEL)
    {
        m_Exit = true;
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<EndScreenState>();
        return;
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<EndScreenState>();
            ServiceLocator::GetSoundManager().Play(7, 100);
            return;
        }
    }
}

std::unique_ptr<LevelState> VersusPlayerState3::OnExit(dae::Scene&)
{
    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (elapsed.count() >= m_EndLevelDelay)
        {
            break;
        }
    }

    return std::move(m_NextState);
}


std::unique_ptr<LevelState> EndScreenState::OnExit(dae::Scene& scene)
{
    scene.RemoveAll();
    return std::move(m_NextState);
}

void EndScreenState::OnEnter(dae::Scene& scene)
{
    EventObserver::GetInstance().AddListener(this);
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("EndScreen");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
    scene.RemoveAll();

    std::vector<ScoreDisplayComponent*> persistentObjects{};
    auto newSceneObjects = newScene.GetPersistentObjects();
    for (auto& object : *newSceneObjects)
    {
        if (ScoreDisplayComponent* scoreComponent = object->GetComponent<ScoreDisplayComponent>())
        {
            persistentObjects.push_back(scoreComponent);
        }
        if (auto textComponent = object->GetComponent<TextComponent>())
        {
            textComponent->m_ShouldRender = false;
        }
    }

    auto highScoreManager = std::make_unique<GameObject>();
    highScoreManager->AddComponent(std::make_unique<HighScoreManagerComponent>(highScoreManager.get(), newScene, glm::vec2{ gWindowWidth, gWindowHeight }, persistentObjects));
    newScene.Add(std::move(highScoreManager));
}

void EndScreenState::HandleEvent(const Event& event)
{
    if (event.type == EventType::SKIP_LEVEL)
    {
        EventObserver::GetInstance().RemoveListener(this);
        m_NextState = std::make_unique<MainMenuState>();
        m_Exit = true;
    }
}