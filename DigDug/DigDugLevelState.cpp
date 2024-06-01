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

using namespace dae;
SinglePlayerState1::SinglePlayerState1()
{
}

SinglePlayerState1::~SinglePlayerState1()
{
    
}

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
    auto go = std::make_unique<dae::GameObject>();

    std::shared_ptr<dae::Font> font = std::move(resourceManager.LoadFont("Lingua.otf", 36));

    //Score Display Event Handler
    go = std::make_unique<dae::GameObject>();
    font = std::move(resourceManager.LoadFont("Lingua.otf", 24));
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player0"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 0, 0, 0, 255 });
    go->SetWorldPosition(5, 10);
    newScene.AddPersistentObject(std::move(go));

    //Lives Display Event Handler
    go = std::make_unique<dae::GameObject>();
    font = std::move(resourceManager.LoadFont("Lingua.otf", 24));
    go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
    go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player0"));
    go->GetComponent<dae::TextComponent>()->SetColor({ 0, 0, 0, 255 });
    go->SetWorldPosition(5, 20);
    newScene.AddPersistentObject(std::move(go));

	auto& tunnelManager = TunnelManager::GetInstance();

	tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

	newScene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    pLevelLoader->CreateEntities(newScene);
}

std::unique_ptr<LevelState> SinglePlayerState1::OnExit(dae::Scene&)
{
    return std::move(m_NextState);
}

void SinglePlayerState1::HandleEvent(const Event& event)
{
    if (event.type == EventType::LOAD_LEVEL)
    {
        EventObserver::GetInstance().RemoveListener(this);
    }
}

MainMenuState::MainMenuState() :
	LevelState::LevelState()
{
}

MainMenuState::~MainMenuState()
{
  
}

void MainMenuState::OnEnter(dae::Scene& scene)
{
    auto mainMenuController = std::make_unique<GameObject>();
    mainMenuController->AddComponent(std::make_unique<dae::MainMenuController>(mainMenuController.get(), gWindowWidth, gWindowHeight, scene));
    scene.Add(std::move(mainMenuController));
}

std::unique_ptr<LevelState> MainMenuState::OnExit(dae::Scene& scene)
{
    scene.RemoveAll();
    return std::move(m_NextState);
}

void MainMenuState::HandleEvent(const Event& event)
{
    if (event.type == EventType::LOAD_LEVEL)
    {
        EventObserver::GetInstance().RemoveListener(this);
        if (event.stringValue == "Level0")
        {
            m_NextState = std::make_unique<SinglePlayerState1>();
            m_Exit = true;
        }
    }
}