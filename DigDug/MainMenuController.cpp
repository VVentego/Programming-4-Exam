#include "MainMenuController.h"
#include <TextComponent.h>
using namespace dae;

MainMenuController::MainMenuController(GameObject* pOwner) :
	Component::Component(pOwner)
{
	auto& resourceManager = ResourceManager::GetInstance();

	std::shared_ptr<Font> font = std::move(resourceManager.LoadFont("Lingua.otf", 14));

	pOwner->AddComponent(std::make_unique<TextComponent>("Single Player", font, pOwner));
	pOwner->AddComponent(std::make_unique<TextComponent>("Multiplayer", font, pOwner));
	pOwner->AddComponent(std::make_unique<TextComponent>("Versus", font, pOwner));
}

void dae::MainMenuController::Update(const double)
{
	HandleInput();
}

void dae::MainMenuController::HandleInput()
{
}

void dae::MainMenuController::MoveDown()
{
	++m_SelectionIdx;
	if (m_SelectionIdx > m_MaxOptions)
	{
		m_SelectionIdx = 0;
	}
}

void dae::MainMenuController::MoveUp()
{
	--m_SelectionIdx;
	if (m_SelectionIdx < 0)
	{
		m_SelectionIdx = m_MaxOptions;
	}
}

void dae::MainMenuController::Shoot()
{
	switch (m_SelectionIdx)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}
}