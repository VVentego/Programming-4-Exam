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
#include "GameObject.h"
#include "TextComponent.h"
#include "FpsCounterComponent.h"
#include "TextureComponent.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent("TextureComponent", std::make_shared<dae::TextureComponent>());
	dynamic_cast<dae::TextureComponent*>(go->GetComponent("TextureComponent").get())->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent("TextureComponent", std::make_shared<dae::TextureComponent>());
	dynamic_cast<dae::TextureComponent*>(go->GetComponent("TextureComponent").get())->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent("TextComponent", std::make_shared<dae::TextComponent>("Programming 4 Assignment", font));
	go->SetPosition(80, 20);
	scene.Add(go);

	float offset{ 5 };
	go = std::make_shared<dae::GameObject>();
	go->AddComponent("TextComponent", std::make_shared<dae::FpsCounterComponent>(font));
	go->SetPosition(offset, offset);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}