#include "HighScoreManagerComponent.h"
#include <TextureComponent.h>
#include <Scene.h>
#include "ScoreDisplayComponent.h"
#include <TextComponent.h>
#include <Player.h>

dae::HighScoreManagerComponent::HighScoreManagerComponent(GameObject* pOwner, Scene& scene, const glm::vec2 screenDimensions, std::vector<ScoreDisplayComponent*> persistentObjects) :
	Component::Component(pOwner), m_HighScoreHandler{ "../data/highscores.dat" } 
{
	std::string playerName{ persistentObjects[0]->GetPlayerName() };
	m_PlayerScore = persistentObjects[0]->GetScore();

	if (persistentObjects.size() > 1)
	{
		if (persistentObjects[0]->GetScore() < persistentObjects[1]->GetScore())
		{
			playerName = persistentObjects[1]->GetPlayerName();
			m_PlayerScore = persistentObjects[1]->GetScore();
		}
	}

	ServiceLocator::GetInputManager().AddPlayer1(*this);
	ServiceLocator::GetInputManager().AddPlayer2(*this);

	m_AllowNameInput = m_HighScoreHandler.IsNewHighScore(m_PlayerScore);
	auto& resourceManager = ResourceManager::GetInstance();
	std::shared_ptr<dae::Font> font = resourceManager.LoadFont("Lingua.otf", 24);

	if (m_AllowNameInput)
	{
		for (int i{}; i <= m_MaxOptions; ++i)
		{
			m_Letters.emplace_back(LetterSelection{});
		}
		auto selectionHighlight = std::make_unique<GameObject>();
		m_SelectionHighlight = selectionHighlight.get();
		selectionHighlight->AddComponent(std::make_unique<TextureComponent>(selectionHighlight.get()));
		selectionHighlight->GetComponent<TextureComponent>()->SetTexture("SelectionBackdrop.png");
		selectionHighlight->SetParent(pOwner);
		scene.Add(std::move(selectionHighlight));

		for (auto& letter : m_Letters)
		{
			auto letterText = std::make_unique<GameObject>();
			letterText->AddComponent(std::make_unique<TextComponent>(std::string(letter.GetChar(), 1), font, letterText.get()));
			m_LetterDisplays.push_back(letterText->GetComponent<TextComponent>());
			m_LetterDisplayObjects.push_back(letterText.get());
			letterText->SetParent(pOwner);
			scene.Add(std::move(letterText));
		}


		for (size_t i{}; i < m_LetterDisplays.size(); ++i)
		{
			m_LetterDisplayObjects[i]->SetLocalPosition(m_LetterSpacing * i + screenDimensions.x / 9.f, 80);
		}
		m_SelectionHighlight->SetLocalPosition(m_LetterDisplayObjects[0]->GetLocalPosition());
		m_SelectionHighlight->GetComponent<TextureComponent>()->SetSize(m_LetterDisplays[0]->GetSize());
	}

	auto scoreDisplay = std::make_unique<GameObject>();
	scoreDisplay->AddComponent(std::make_unique<TextComponent>("High score:", font, scoreDisplay.get()));
	std::string playerNr{ playerName.back() };
	playerName.pop_back();
	font = resourceManager.LoadFont("Lingua.otf", 20);
	scoreDisplay->GetComponent<TextComponent>()->SetText(playerName + " " + playerNr + std::string{ " Score: " } + std::to_string(m_PlayerScore));
	scoreDisplay->SetWorldPosition(screenDimensions.x / 7.f - scoreDisplay->GetComponent<TextComponent>()->GetSize().x / 2.f, 40);
	scene.Add(std::move(scoreDisplay));
	auto title = std::make_unique<GameObject>();
	title->AddComponent(std::make_unique<TextComponent>("HIGH SCORES", font, title.get()));
	title->SetWorldPosition(screenDimensions.x / 7.f - title->GetComponent<TextComponent>()->GetSize().x / 2.f, 10);
	scene.Add(std::move(title));

	float lastYPos{ 120.f };
	for (auto& score : m_HighScoreHandler.GetScores())
	{
		float offset{ 20.f };
		auto scoreObject = std::make_unique<GameObject>();
		std::string highScoreName{};
		for (auto& character : score.name)
		{
			if (character == '\0')
			{
				break;
			}
			highScoreName.push_back(character);
		}
		scoreObject->AddComponent(std::make_unique<TextComponent>("BKN: 99", font, scoreObject.get()));
		scoreObject->GetComponent<TextComponent>()->SetText(highScoreName.append(std::string(": ")).append(std::to_string(score.score)));
		scoreObject->SetWorldPosition(screenDimensions.x / 7.f - scoreObject->GetComponent<TextComponent>()->GetSize().x / 2.f, lastYPos);
		m_ScoreDisplays.push_back(scoreObject.get());
		scene.Add(std::move(scoreObject));
		lastYPos += offset;
	}
}

dae::HighScoreManagerComponent::~HighScoreManagerComponent()
{
	ServiceLocator::GetInputManager().RemovePlayer1();
	ServiceLocator::GetInputManager().RemovePlayer2();
}

void dae::HighScoreManagerComponent::HandleInput(Command* command)
{
	if (command != nullptr)
	{
		command->Execute(this);
	}
}

void dae::HighScoreManagerComponent::MoveRight()
{
	if (m_AllowNameInput)
	{
		++m_SelectionIdx;
		if (m_SelectionIdx > m_MaxOptions)
		{
			m_SelectionIdx = 0;
		}
		m_SelectionHighlight->SetLocalPosition(m_LetterDisplayObjects[m_SelectionIdx]->GetLocalPosition());
		m_SelectionHighlight->GetComponent<TextureComponent>()->SetSize(m_LetterDisplayObjects[m_SelectionIdx]->GetComponent<TextComponent>()->GetSize());
		ServiceLocator::GetSoundManager().Play(8, 100);
	}
}

void dae::HighScoreManagerComponent::MoveDown()
{
	if (m_AllowNameInput)
	{
		m_Letters[m_SelectionIdx].SelectDown();
		m_LetterDisplays[m_SelectionIdx]->SetText(std::string(m_Letters[m_SelectionIdx].GetChar(), 1));
	}
}

void dae::HighScoreManagerComponent::MoveLeft()
{
	if (m_AllowNameInput)
	{
		--m_SelectionIdx;
		if (m_SelectionIdx < 0)
		{
			m_SelectionIdx = m_MaxOptions;
		}
		m_SelectionHighlight->SetLocalPosition(m_LetterDisplayObjects[m_SelectionIdx]->GetLocalPosition());
		m_SelectionHighlight->GetComponent<TextureComponent>()->SetSize(m_LetterDisplayObjects[m_SelectionIdx]->GetComponent<TextComponent>()->GetSize());
		ServiceLocator::GetSoundManager().Play(8, 100);
	}
}

void dae::HighScoreManagerComponent::MoveUp()
{
	if (m_AllowNameInput)
	{
		m_Letters[m_SelectionIdx].SelectUp();
		m_LetterDisplays[m_SelectionIdx]->SetText(std::string(m_Letters[m_SelectionIdx].GetChar(), 1));
	}
}

void dae::HighScoreManagerComponent::Shoot()
{
	if (m_AllowNameInput)
	{
		std::string playerName{};
		for (auto& letter : m_Letters)
		{
			playerName.push_back(*letter.GetChar());
		}
		m_HighScoreHandler.AddHighScore(playerName, m_PlayerScore);
		m_AllowNameInput = false;

		auto& newScores = m_HighScoreHandler.GetScores();

		for (size_t i{}; i < newScores.size(); ++i)
		{
			if (newScores[i].score == m_PlayerScore)
			{
				// Ensure the index is within bounds
				if (i < m_ScoreDisplays.size()) {
					// Construct the new display text
					std::string newText = playerName + ": " + std::to_string(m_PlayerScore);

					m_ScoreDisplays[i]->GetComponent<TextComponent>()->SetText(newText);
					break;
				}
			}
		}

		for (auto& letter : m_LetterDisplayObjects)
		{
			letter->Destroy();
		}
		m_LetterDisplayObjects.clear();
		m_SelectionHighlight->Destroy();
		ServiceLocator::GetSoundManager().Play(8, 100);
	}
}

void dae::HighScoreManagerComponent::Mute()
{
	ServiceLocator::GetSoundManager().ToggleMute();
}

void dae::HighScoreManagerComponent::Skip()
{
	Event event{};
	event.type = EventType::SKIP_LEVEL;
	NotifyObserver(event);
}

dae::LetterSelection::LetterSelection(LetterSelection&& other) noexcept
{
	other.m_CurrentSelection = m_CurrentSelection;
}

dae::LetterSelection& dae::LetterSelection::operator=(LetterSelection&& other) noexcept
{
	other.m_CurrentSelection = m_CurrentSelection;

	return *this;
}

void dae::LetterSelection::SelectUp()
{
	if (static_cast<unsigned int>(m_CurrentSelection) < m_LargestLetter)
	{
		++m_CurrentSelection;
	}
	else
	{
		m_CurrentSelection = static_cast<char>(m_SmallestLetter);
	}
}

void dae::LetterSelection::SelectDown()
{
	if (static_cast<unsigned int>(m_CurrentSelection) > m_SmallestLetter)
	{
		--m_CurrentSelection;
	}
	else
	{
		m_CurrentSelection = static_cast<char>(m_LargestLetter);
	}
}
