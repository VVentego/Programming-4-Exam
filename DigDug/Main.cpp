#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "../Minigin/Minigin.h"
#include "../Minigin/Scene.h"
#include <iostream>
#include "ComponentsHeader.h"
#include "../Minigin/ServiceLocator.h"
#include "TunnelManager.h"
#include "LevelLoader.h"

void CreateUI(dae::Scene& scene);
void CreateBackground(dae::Scene& scene, const std::string& backgroundPath);
void CreateEntities(const std::vector<Player>& players, const std::vector<glm::vec2>& pookas, dae::Scene& scene);
void LoadSounds(dae::SoundSystem& soundManager);

void load()
{
	using namespace dae;
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& soundManager = ServiceLocator::GetSoundManager();
	auto& tunnelManager = TunnelManager::GetInstance();
	Renderer::GetInstance().SetBackgroundColor(SDL_Color{ 0,28,128,255 });

	std::unique_ptr<LevelLoader> pLevelLoader{ std::make_unique<LevelLoader>() };

	pLevelLoader->LoadLevel("../Data/Level0.lua");

	CreateBackground(scene, pLevelLoader->GetBackground());

	tunnelManager.Init("TunnelHorizontal.png", pLevelLoader->GetTunnels());

	scene.Add(std::unique_ptr<GameObject>(tunnelManager.GetTunnelManagerObject()));

	LoadSounds(soundManager);

	CreateUI(scene);

	CreateEntities(pLevelLoader->GetPlayers(), pLevelLoader->GetPookas(), scene);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}

void CreateUI(dae::Scene& scene)
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
	go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player1"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	go->SetWorldPosition(5, gWindowHeight - 100);
	scene.Add(std::move(go));

	//Score Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(resourceManager.LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::ScoreDisplayComponent>(go.get(), "Player2"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	go->SetWorldPosition(5, gWindowHeight - 150);
	scene.Add(std::move(go));

	//Lives Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(resourceManager.LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player1"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	go->SetWorldPosition(5, gWindowHeight - 125);
	scene.Add(std::move(go));

	//Lives Display Event Handler
	go = std::make_unique<dae::GameObject>();
	font = std::move(resourceManager.LoadFont("Lingua.otf", 24));
	go->AddComponent(std::make_unique<dae::TextComponent>("Score: 50", font, go.get()));
	go->AddComponent(std::make_unique<dae::LivesDisplayComponent>(go.get(), "Player2"));
	go->GetComponent<dae::TextComponent>()->SetColor({ 255, 255, 255, 255 });
	go->SetWorldPosition(5, gWindowHeight - 175);
	scene.Add(std::move(go));
}

void CreateBackground(dae::Scene& scene, const std::string& backgroundPath)
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto go = std::make_unique<dae::GameObject>();

	go->AddComponent(std::make_unique<dae::TextureComponent>(go.get()));
	go->GetComponent<dae::TextureComponent>()->SetTexture(backgroundPath);
	scene.Add(std::move(go));
}

void CreateEntities(const std::vector<Player>& players, const std::vector<glm::vec2>& pookas, dae::Scene& scene)
{
	auto& resourceManager = dae::ResourceManager::GetInstance();
	std::vector<dae::GameObject*> digdugs;

	for (auto& player : players)
	{
		auto pump = std::make_unique<dae::GameObject>();

		pump->AddComponent(std::make_unique<dae::PumpBehaviorComponent>(pump.get(), 0));
		pump->AddCollider(scene);

		auto digdug = std::make_unique<dae::GameObject>();
		digdug->AddComponent(std::make_unique<dae::SpriteAnimatorComponent>(digdug.get()));
		digdug->GetComponent<dae::SpriteAnimatorComponent>()->AddSpriteSheet("DigDugMoveRight.png", 1, 2);
		digdug->SetWorldPosition(player.position.x, player.position.y);
		digdug->AddComponent(std::make_unique<dae::DigDugController>(digdug.get(), std::string("Player").append(std::to_string(player.id)),
			dae::ControllerInfo{ player.usesController, player.usesController }, pump.get()));
		digdug->AddCollider(scene);

		digdugs.push_back(digdug.get());

		scene.Add(std::move(digdug));
		scene.Add(std::move(pump));
	}

	for (auto& pookaPos : pookas)
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

void LoadSounds(dae::SoundSystem& soundManager)
{
	soundManager.AddTrack("pump_fire.wav", 0);
	soundManager.AddTrack("pump.wav", 1);
	soundManager.AddTrack("enemy_killed1.wav", 2);
	soundManager.AddTrack("enemy_pop.wav", 3);
	soundManager.AddTrack("life_lost.wav", 4);
}