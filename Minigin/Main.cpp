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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent("TextureComponent", std::make_unique<dae::TextureComponent>(go.get()));
	dynamic_cast<dae::TextureComponent*>(go->GetComponent("TextureComponent").get())->SetTexture("background.tga");

	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent("TextureComponent", std::make_unique<dae::TextureComponent>(go.get()));
	dynamic_cast<dae::TextureComponent*>(go->GetComponent("TextureComponent").get())->SetTexture("logo.tga");
	go->SetWorldPosition(216, 180, 0);
	scene.Add(std::move(go));

	std::shared_ptr<dae::Font> font = std::move(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	go = std::make_unique<dae::GameObject>();
	go->AddComponent("TextComponent", std::make_unique<dae::TextComponent>("Programming 4 Assignment", font, go.get()));
	go->SetWorldPosition(80, 20, 0);
	scene.Add(std::move(go));

	float offset{ 5 };
	go = std::make_unique<dae::GameObject>();
	go->AddComponent("TextComponent", std::make_unique<dae::TextComponent>("60.0", font, go.get()));
	go->AddComponent("FpsCounterComponent", std::make_unique<dae::FpsCounterComponent>(go.get()));
	go->SetWorldPosition(offset, offset, 0);
	scene.Add(std::move(go));

	auto digdug = std::make_unique<dae::GameObject>();
	digdug->AddComponent("TextureComponent", std::make_unique<dae::TextureComponent>(digdug.get()));
	dynamic_cast<dae::TextureComponent*>(digdug->GetComponent("TextureComponent").get())->SetTexture("digdug.png");
	digdug->SetWorldPosition(200, 300, 0);
	digdug->AddComponent("RotatorComponent", std::make_unique<dae::RotatorComponent>(digdug.get(), digdug->GetWorldPosition(), 30.f, 5.f));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent("TextureComponent", std::make_unique<dae::TextureComponent>(go.get()));
	dynamic_cast<dae::TextureComponent*>(go->GetComponent("TextureComponent").get())->SetTexture("dingus.png");
	go->SetWorldPosition(250, 300, 0);
	go->SetParent(digdug.get(), false);
	go->AddComponent("RotatorComponent", std::make_unique<dae::RotatorComponent>(go.get(), glm::vec3{ 0, 0, 0 }, 50.f, 5.f));
	scene.Add(std::move(go));

	scene.Add(std::move(digdug));

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}