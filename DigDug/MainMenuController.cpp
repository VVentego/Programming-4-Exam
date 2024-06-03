#include "MainMenuController.h"
#include <TextComponent.h>
#include <Scene.h>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace dae;

MainMenuController::MainMenuController(GameObject* pOwner, const int windowWidth, const int windowHeight, Scene& scene) :
	Component::Component(pOwner)
{
	//Register self as player 1
	ServiceLocator::GetInputManager().AddPlayer1(*this);
	auto& resourceManager = ResourceManager::GetInstance();
	const float spacing{ 40 };

	std::shared_ptr<Font> font = std::move(resourceManager.LoadFont("Lingua.otf", 14));
	std::unique_ptr<GameObject> textObject = std::make_unique<GameObject>();
	textObject->AddComponent(std::make_unique<TextComponent>("Single Player", font, textObject.get()));
	textObject->SetParent(pOwner);
	textObject->SetWorldPosition(windowWidth / static_cast<float>(2), windowHeight - spacing);
	scene.Add(std::move(textObject));

	textObject = std::make_unique<GameObject>();
	textObject->AddComponent(std::make_unique<TextComponent>("Multiplayer", font, textObject.get()));
	textObject->SetParent(pOwner);
	textObject->SetWorldPosition(windowWidth / static_cast<float>(2), windowHeight - spacing * 2);
	scene.Add(std::move(textObject));
	
	textObject = std::make_unique<GameObject>();
	textObject->AddComponent(std::make_unique<TextComponent>("Versus", font, textObject.get()));
	textObject->SetParent(pOwner);
	textObject->SetWorldPosition(windowWidth / static_cast<float>(2), windowHeight - spacing * 3);
	scene.Add(std::move(textObject));
}

dae::MainMenuController::~MainMenuController()
{
	ServiceLocator::GetInputManager().RemovePlayer1();
}

void dae::MainMenuController::Update(const double)
{
}

void dae::MainMenuController::HandleInput(Command* command)
{
	if (command != nullptr)
	{
		command->Execute(this);
	}
}

void dae::MainMenuController::MoveDown()
{
	++m_SelectionIdx;
	if (m_SelectionIdx > m_MaxOptions)
	{
		m_SelectionIdx = 0;
	}
#ifdef _DEBUG
	std::cout << "Menu selection = " << std::to_string(m_SelectionIdx) << std::endl;
#endif
}

void dae::MainMenuController::MoveUp()
{
	--m_SelectionIdx;
	if (m_SelectionIdx < 0)
	{
		m_SelectionIdx = m_MaxOptions;
	}
#ifdef _DEBUG
	std::cout << "Menu selection = " << std::to_string(m_SelectionIdx) << std::endl;
#endif
}

void dae::MainMenuController::Shoot()
{
	Event loadLevelEvent{};
	loadLevelEvent.type = EventType::LOAD_LEVEL;
	switch (m_SelectionIdx)
	{
	case 0:
		loadLevelEvent.stringValue = "Level0";
		EventObserver::GetInstance().Notify(loadLevelEvent);
		break;
	case 1:
		loadLevelEvent.stringValue = "CoopLevel0";
		EventObserver::GetInstance().Notify(loadLevelEvent);
		break;
	case 2:
		loadLevelEvent.stringValue = "VersusLevel0";
		EventObserver::GetInstance().Notify(loadLevelEvent);
		break;
	}
}