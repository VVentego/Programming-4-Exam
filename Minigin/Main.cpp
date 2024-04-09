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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto observer = std::make_shared<dae::PlayerObserver>();

	//auto go = std::make_unique<dae::GameObject>();
	//go->AddComponent(std::make_unique<dae::TextureComponent>(go.get(), static_cast<float>(gWindowWidth), static_cast<float>(gWindowWidth)));
	//go->GetComponent<dae::TextureComponent>()->SetTexture("Level1.png");
	//scene.Add(std::move(go));
	
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent(std::make_unique<dae::TextureComponent>(go.get()));
	go->GetComponent<dae::TextureComponent>()->SetTexture("background.tga");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent(std::make_unique<dae::TextureComponent>(go.get()));
	go->GetComponent<dae::TextureComponent>()->SetTexture("logo.tga");
	go->SetWorldPosition(216, 180, 0);
	scene.Add(std::move(go));

	std::shared_ptr<dae::Font> font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	//go = std::make_unique<dae::GameObject>();
	//go->AddComponent(std::make_unique<dae::TextComponent>("Programming 4 Assignment", font, go.get()));
	//go->GetComponent<dae::TextComponent>()->SetColor({ 255, 0, 0, 255 });
	//go->SetWorldPosition(80, 20, 0);
	//scene.Add(std::move(go));

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
	go->SetWorldPosition(5, 50, 0);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14));
	go->AddComponent(std::make_unique<dae::TextComponent>("Use WASD to move Dig Dug, C to inflict damage, Z and X to attack.", font, go.get()));
	go->SetWorldPosition(5, 75, 0);
	scene.Add(std::move(go));

	//Score Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player1"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	observer->AddSubject(go->GetComponent<dae::ScoreDisplayComponent>());
	go->SetWorldPosition(5, 100, 0);
	scene.Add(std::move(go));

	//Score Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player2"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	go->SetWorldPosition(5, 150, 0);
	observer->AddListener(go->GetComponent<dae::ScoreDisplayComponent>());
	scene.Add(std::move(go));

	//Lives Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	observer->AddListener(go->GetComponent<dae::LivesDisplayComponent>());
	go->SetWorldPosition(5, 125, 0);
	scene.Add(std::move(go));

	//Lives Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player2"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	go->SetWorldPosition(5, 175, 0);
	observer->AddListener(go->GetComponent<dae::LivesDisplayComponent>());
	scene.Add(std::move(go));
	
	auto digdug = std::make_unique<dae::GameObject>();
	digdug->AddComponent(std::make_unique<dae::SpriteAnimatorComponent>(digdug.get()));
	digdug->GetComponent<dae::SpriteAnimatorComponent>()->AddSpriteSheet("DigDugMoveRight.png", 1, 2);
	digdug->SetWorldPosition(200, 300, 0);
	digdug->AddComponent(std::make_unique<dae::PlayerController>(digdug.get(), "Player1", false));
	digdug->GetComponent<dae::PlayerController>()->AddObserver(observer);

	go = std::make_unique<dae::GameObject>();
	go->AddComponent(std::make_unique<dae::SpriteAnimatorComponent>(go.get()));
	go->GetComponent<dae::SpriteAnimatorComponent>()->AddSpriteSheet("PookaMoveRight.png", 1, 2);
	go->SetWorldPosition(250, 300, 0);
	go->AddComponent(std::make_unique<dae::PlayerController>(go.get(), "Player2", true));
	go->GetComponent<dae::PlayerController>()->AddObserver(observer);

	scene.Add(std::move(go));
	scene.Add(std::move(digdug));
	scene.AddObserver(std::move(observer));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}