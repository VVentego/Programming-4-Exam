#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include <iostream>

void CreateUI(dae::Scene& scene, dae::PlayerObserver* pObserver);
void CreatePlayer1(glm::vec2 position, dae::Scene& scene, std::shared_ptr<dae::PlayerObserver> pObserver, dae::TunnelManagerComponent* pTunnelManager);


void load()
{
	using namespace dae;
	auto observer = std::make_shared<PlayerObserver>();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//auto go = std::make_unique<dae::GameObject>();
	//go->AddComponent(std::make_unique<dae::TextureComponent>(go.get(), static_cast<float>(gWindowWidth), static_cast<float>(gWindowWidth)));
	//go->GetComponent<dae::TextureComponent>()->SetTexture("Level1.png");
	//scene.Add(std::move(go));
	
	//auto go = std::make_unique<dae::GameObject>();
	//go->AddComponent(std::make_unique<dae::TextureComponent>(go.get()));
	//go->GetComponent<dae::TextureComponent>()->SetTexture("background.tga");
	//scene.Add(std::move(go));
	std::unique_ptr<GameObject> tunnelManager{ std::make_unique<GameObject>() };
	tunnelManager->AddComponent(std::make_unique<TunnelManagerComponent>(tunnelManager.get(), "tunnel.png"));
	CreateUI(scene, observer.get());
	//go = std::make_unique<dae::GameObject>();
	//go->AddComponent(std::make_unique<dae::TextComponent>("Programming 4 Assignment", font, go.get()));
	//go->GetComponent<dae::TextComponent>()->SetColor({ 255, 0, 0, 255 });
	//go->SetWorldPosition(80, 20, 0);
	//scene.Add(std::move(go));

	CreatePlayer1({ 200, gWindowHeight - 300 }, scene, observer, tunnelManager->GetComponent<TunnelManagerComponent>());

	//go = std::make_unique<dae::GameObject>();
	//go->AddComponent(std::make_unique<dae::SpriteAnimatorComponent>(go.get()));
	//go->GetComponent<dae::SpriteAnimatorComponent>()->AddSpriteSheet("PookaMoveRight.png", 1, 2);
	//go->SetWorldPosition(250, 300, 0);
	//go->AddComponent(std::make_unique<dae::DigDugController>(go.get(), "Player2", true));
	//go->GetComponent<dae::DigDugController>()->AddObserver(observer);

	//scene.Add(std::move(go));
	scene.Add(std::move(tunnelManager));
	scene.AddObserver(std::move(observer));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}

void CreateUI(dae::Scene& scene, dae::PlayerObserver* observer)
{
	auto go = std::make_unique<dae::GameObject>();

	go->AddComponent(std::make_unique<dae::TextureComponent>(go.get()));
	go->GetComponent<dae::TextureComponent>()->SetTexture("logo.tga");
	go->SetWorldPosition(216, gWindowHeight - 180, 0);
	scene.Add(std::move(go));

	std::shared_ptr<dae::Font> font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));

	float offset{ 5 };
	go = std::make_unique<dae::GameObject>();
	go->AddComponent(std::make_unique<dae::TextComponent>("60.0", font, go.get()));
	go->AddComponent(std::make_unique<dae::FpsCounterComponent>(go.get()));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 0, 0, 255 });
	go->SetWorldPosition(offset, offset, 0);
	scene.Add(std::move(go));

	//Instructions
	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14));
	go->AddComponent(std::make_unique<dae::TextComponent>("Use the D-Pad to move the Pooka, X to inflict damage, A and B to attack the Player.", font, go.get()));
	go->SetWorldPosition(5, gWindowHeight - 50, 0);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14));
	go->AddComponent(std::make_unique<dae::TextComponent>("Use WASD to move Dig Dug, C to inflict damage, Z and X to attack.", font, go.get()));
	go->SetWorldPosition(5, gWindowHeight - 75, 0);
	scene.Add(std::move(go));


	//Score Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player1"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	observer->AddSubject(go->GetComponent<dae::ScoreDisplayComponent>());
	go->SetWorldPosition(5, gWindowHeight - 100, 0);
	scene.Add(std::move(go));

	//Score Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player2"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	go->SetWorldPosition(5, gWindowHeight - 150, 0);
	observer->AddListener(go->GetComponent<dae::ScoreDisplayComponent>());
	scene.Add(std::move(go));

	//Lives Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	observer->AddListener(go->GetComponent<dae::LivesDisplayComponent>());
	go->SetWorldPosition(5, gWindowHeight - 125, 0);
	scene.Add(std::move(go));

	//Lives Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player2"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	go->SetWorldPosition(5, gWindowHeight - 175, 0);
	observer->AddListener(go->GetComponent<dae::LivesDisplayComponent>());
	scene.Add(std::move(go));
}

void CreatePlayer1(glm::vec2 position, dae::Scene& scene, std::shared_ptr<dae::PlayerObserver> pObserver, dae::TunnelManagerComponent* pTunnelManager)
{
	std::vector<std::shared_ptr<dae::Texture2D>> pumpTextures;
	pumpTextures.push_back(dae::ResourceManager::GetInstance().LoadTexture("PumpRight.png"));
	pumpTextures.push_back(dae::ResourceManager::GetInstance().LoadTexture("PumpDown.png"));
	pumpTextures.push_back(dae::ResourceManager::GetInstance().LoadTexture("PumpLeft.png"));
	pumpTextures.push_back(dae::ResourceManager::GetInstance().LoadTexture("PumpUp.png"));

	auto pump = std::make_unique<dae::GameObject>();
	pump->AddComponent(std::make_unique<dae::TextureComponent>(pump.get()));
	pump->AddComponent(std::make_unique<dae::PumpBehaviorComponent>(pump.get(), std::move(pumpTextures)));

	auto digdug = std::make_unique<dae::GameObject>();
	digdug->AddComponent(std::make_unique<dae::SpriteAnimatorComponent>(digdug.get()));
	digdug->GetComponent<dae::SpriteAnimatorComponent>()->AddSpriteSheet("DigDugMoveRight.png", 1, 2);
	digdug->SetWorldPosition(position.x, position.y, 0);
	digdug->AddComponent(std::make_unique<dae::DigDugController>(digdug.get(), "Player1", false, pump.get()));
	digdug->GetComponent<dae::DigDugController>()->AddObserver(pObserver);
	digdug->GetComponent<dae::DigDugController>()->SetTunnelManager(pTunnelManager);

	scene.Add(std::move(digdug));
	scene.Add(std::move(pump));
}