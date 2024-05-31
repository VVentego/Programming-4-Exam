#include "DigDugLevelState.h"
#include "LevelLoader.h"
#include <ServiceLocator.h>
#include <memory>
#include "TunnelManager.h"
#include <SceneManager.h>

SinglePlayerState1::SinglePlayerState1()
{
}

void SinglePlayerState1::OnEnter(dae::Scene&)
{
	std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level1");
	SceneManager& sceneManager = SceneManager::GetInstance();
	sceneManager.TransferPersistentObjects(*sceneManager.GetCurrentScene(), scene);
#if _DEBUG
	pLevelLoader->LoadLevel("../Data/Level0.lua");
#else
	pLevelLoader->LoadLevel("../Data/Level0.lub");
#endif // _DEBUG
	auto& tunnelManager = TunnelManager::GetInstance();
	pLevelLoader->CreateBackground(scene);

	tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

	scene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));
    pLevelLoader->CreateEntities(scene);

	pLevelLoader->CreateUI(scene);
}

void SinglePlayerState1::OnExit(dae::Scene&)
{
}

void SinglePlayerState1::HandleEvent()
{
}


MainMenuState::MainMenuState() :
	LevelState::LevelState()
{
}

void MainMenuState::OnEnter(dae::Scene&)
{
}

void MainMenuState::OnExit(dae::Scene&)
{
}

void MainMenuState::HandleEvent()
{
}