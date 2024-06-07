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
	std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
	auto& newScene = dae::SceneManager::GetInstance().CreateScene("Level1");
	SceneManager& sceneManager = SceneManager::GetInstance();
	sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
	pLevelLoader->LoadLevel("../Data/Level0.lua");
#else
	pLevelLoader->LoadLevel("../Data/Level0.lub");
#endif // _DEBUG
	pLevelLoader->CreateBackground(newScene);
    
    auto& resourceManager = dae::ResourceManager::GetInstance();

    //Score Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 24);
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player0"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, gWindowHeight - 24);
    newScene.AddPersistentObject(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player0"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

	auto& tunnelManager = TunnelManager::GetInstance();

	tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

	newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    m_EnemiesLeft = pLevelLoader->CreateEntities(newScene);
}

std::unique_ptr<LevelState> SinglePlayerState1::OnExit(dae::Scene&)
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

    ServiceLocator::GetSoundManager().Play(7, 100);
    return std::move(m_NextState);
}

void SinglePlayerState1::HandleEvent(const Event& event)
{
    if (event.type == EventType::PLAYER_DIED)
    {
        if (event.stringValue == "Player0")
        {
            --m_Player0Lives;
            if (m_Player0Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::LOAD_LEVEL)
    {
        EventObserver::GetInstance().RemoveListener(this);
    }

    if (event.type == EventType::ENEMY_KILLED)
    {
        --m_EnemiesLeft;
        if (m_EnemiesLeft <= 0)
        {
            m_Exit = true;
            EventObserver::GetInstance().RemoveListener(this);
            m_NextState = std::make_unique<EndScreenState>();
        }
    }
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
    std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("versus1");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
#if _DEBUG
    pLevelLoader->LoadLevel("../Data/Level1Versus.lua");
#else
    pLevelLoader->LoadLevel("../Data/Level1Versus.lub");
#endif // _DEBUG
    pLevelLoader->CreateBackground(newScene);

    auto& resourceManager = dae::ResourceManager::GetInstance();

    //Score Display Event Handler
    auto go = std::make_unique<dae::GameObject>();
    std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 24);
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player0"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, gWindowHeight - 24);
    newScene.AddPersistentObject(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player0"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 10);
    newScene.Add(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
    go->SetWorldPosition(5, 40);
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
        if (event.stringValue == "Player0")
        {
            --m_Player0Lives;
            if (m_Player0Lives <= 0)
            {
                m_Exit = true;
                EventObserver::GetInstance().RemoveListener(this);
                m_NextState = std::make_unique<MainMenuState>();
            }
        }
    }

    if (event.type == EventType::LOAD_LEVEL)
    {
        EventObserver::GetInstance().RemoveListener(this);
    }
}

std::unique_ptr<LevelState> EndScreenState::OnExit(dae::Scene& scene)
{
    scene.RemoveAll();
    return std::move(m_NextState);
}

void EndScreenState::OnEnter(dae::Scene& scene)
{
    auto& newScene = dae::SceneManager::GetInstance().CreateScene("versus1");
    SceneManager& sceneManager = SceneManager::GetInstance();
    sceneManager.TransferPersistentObjects(scene, newScene);
    
    std::vector<ScoreDisplayComponent*> persistentObjects{};
    auto newSceneObjects = newScene.GetPersistentObjects();
    for (auto& object : *newSceneObjects)
    {
        if (ScoreDisplayComponent* scoreComponent = object->GetComponent<ScoreDisplayComponent>())
        {
            persistentObjects.push_back(scoreComponent);
        }
        object->GetComponent<TextComponent>()->m_ShouldRender = false;
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
