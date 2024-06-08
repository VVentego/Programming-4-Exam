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
	auto textComponent{ std::make_unique<TextComponent>("Single Player", font, textObject.get()) };
	auto size = textComponent->GetSize().x;
	textObject->AddComponent(std::move(textComponent));
	textObject->SetParent(pOwner);
	textObject->SetWorldPosition(windowWidth / 4.f - size / 2.f, windowHeight / 2.f - spacing * 4);
	m_ButtonPositions.push_back(textObject->GetWorldPosition());
	scene.Add(std::move(textObject));

	textObject = std::make_unique<GameObject>();
	textComponent = std::make_unique<TextComponent>("Multiplayer", font, textObject.get());
	size = textComponent->GetSize().x;
	textObject->AddComponent(std::move(textComponent));
	textObject->SetParent(pOwner);
	textObject->SetWorldPosition(windowWidth / 4.f - size / 2.f, windowHeight / 2.f - spacing * 3);
	m_ButtonPositions.push_back(textObject->GetWorldPosition());
	scene.Add(std::move(textObject));

	textObject = std::make_unique<GameObject>();
	textComponent = std::make_unique<TextComponent>("Versus", font, textObject.get());
	size = textComponent->GetSize().x;
	textObject->AddComponent(std::move(textComponent));
	textObject->SetParent(pOwner);
	textObject->SetWorldPosition(windowWidth / 4.f - size / 2.f, windowHeight / 2.f - spacing * 2);
	m_ButtonPositions.push_back(textObject->GetWorldPosition());
	scene.Add(std::move(textObject));

	textObject = std::make_unique<GameObject>();
	textComponent = std::make_unique<TextComponent>("High Scores", font, textObject.get());
	size = textComponent->GetSize().x;
	textObject->AddComponent(std::move(textComponent));
	textObject->SetParent(pOwner);
	textObject->SetWorldPosition(windowWidth / 4.f - size / 2.f, windowHeight / 2.f - spacing);
	m_ButtonPositions.push_back(textObject->GetWorldPosition());
	scene.Add(std::move(textObject));

	auto pointer = std::make_unique<GameObject>();
	pointer->AddComponent(std::make_unique<TextureComponent>(pointer.get()));
	pointer->GetComponent<TextureComponent>()->SetTexture("PumpRight.png");
	m_Pointer = pointer.get();
	m_PointerSize = pointer->GetComponent<TextureComponent>()->GetSize();
	m_Pointer->SetWorldPosition(m_ButtonPositions[0].x - m_PointerSize.x, m_ButtonPositions[0].y + m_PointerSize.y / 2.f);
	scene.Add(std::move(pointer));
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
	auto currentTime = std::chrono::steady_clock::now();
	auto holdDuration = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_LastButtonPress);
	if (command != nullptr)
	{
		if (holdDuration >= m_HoldButtonThreshold)
		{
			command->Execute(this);

			m_LastButtonPress = currentTime;
		}
	}
}

void dae::MainMenuController::MoveDown()
{
	++m_SelectionIdx;
	if (m_SelectionIdx > m_MaxOptions)
	{
		m_SelectionIdx = 0;
	}
	const glm::vec2 newPointerPos{ m_ButtonPositions[m_SelectionIdx].x - m_PointerSize.x, m_ButtonPositions[m_SelectionIdx].y + m_PointerSize.y / 2.f };
	m_Pointer->SetWorldPosition(newPointerPos);
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
	const glm::vec2 newPointerPos{ m_ButtonPositions[m_SelectionIdx].x - m_PointerSize.x, m_ButtonPositions[m_SelectionIdx].y + m_PointerSize.y / 2.f };
	m_Pointer->SetWorldPosition(newPointerPos);
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
		loadLevelEvent.stringValue = "Coop";
		EventObserver::GetInstance().Notify(loadLevelEvent);
		break;
	case 2:
		loadLevelEvent.stringValue = "versus";
		EventObserver::GetInstance().Notify(loadLevelEvent);
		break;
	case 3:
		loadLevelEvent.stringValue = "highscore";
		EventObserver::GetInstance().Notify(loadLevelEvent);
		break;
	}
}

void dae::MainMenuController::Mute()
{
	ServiceLocator::GetSoundManager().ToggleMute();
}
