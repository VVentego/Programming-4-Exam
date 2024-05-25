#include "DigDugController.h"
#include "TunnelManager.h"
#include "Enemy.h"
#include <SpriteAnimatorComponent.h>
#include "DigDugState.h"

dae::DigDugController::DigDugController(GameObject* pOwner, const std::string& playerName, GameObject* pPump) :
	Component(pOwner), m_PlayerName{ playerName }, m_pPumpObject{ pPump }, m_CurrentState{ new DigDugNormalState() },
	m_pWalkSpriteRight{ std::make_shared<SpriteSheet>("DigDugMoveRight.png", 1, 2) },
	m_pWalkSpriteDown{ std::make_shared<SpriteSheet>("DigDugMoveDown.png", 1, 2) },
	m_pWalkSpriteLeft{ std::make_shared<SpriteSheet>("DigDugMoveLeft.png", 1, 2) },
	m_pWalkSpriteUp{ std::make_shared<SpriteSheet>("DigDugMoveUp.png", 1, 2) },
	m_pDigSpriteRight{ std::make_shared<SpriteSheet>("DigDugDigRight.png", 1, 2) },
	m_pDigSpriteDown{ std::make_shared<SpriteSheet>("DigDugDigDown.png", 1, 2) },
	m_pDigSpriteLeft{ std::make_shared<SpriteSheet>("DigDugDigLeft.png", 1, 2) },
	m_pDigSpriteUp{ std::make_shared<SpriteSheet>("DigDugDigUp.png", 1, 2) },
	m_pDeathSprite{ std::make_shared<SpriteSheet>("DigDugDeath.png", 1, 4) }
{
	auto digDugSpriteAnimator = std::make_unique<SpriteAnimatorComponent>(pOwner);
	digDugSpriteAnimator->AddSpriteSheet(m_pWalkSpriteRight);
	m_pAnimatorComponent = digDugSpriteAnimator.get();
	pOwner->AddComponent(std::move(digDugSpriteAnimator));
	m_Size = m_pAnimatorComponent->GetSize();
	assert(m_pPumpObject != nullptr);
	m_pPumpObject->SetParent(pOwner, false);

	m_Pump = m_pPumpObject->GetComponent<PumpBehaviorComponent>();
	assert(m_Pump != nullptr);

	EventObserver::GetInstance().AddListener(this);
}

dae::DigDugController::~DigDugController()
{
	delete m_CurrentState;
	m_CurrentState = nullptr;

	if (m_PlayerName == "Player1")
	{
		ServiceLocator::GetInputManager().RemovePlayer1();
	}
	else
	{
		ServiceLocator::GetInputManager().RemovePlayer2();
	}
}

void dae::DigDugController::Update(const double deltaTime)
{
	if (m_Lives > 0)
	{
		auto nextState = m_CurrentState->Update(*this, deltaTime);

		if (nextState != nullptr)
		{
			m_CurrentState->OnExit(*this);
			delete m_CurrentState;
			m_CurrentState = nextState;
			m_CurrentState->OnEnter(*this);
		}
	}
}

void dae::DigDugController::HandleInput(Command* command)
{
	m_CurrentState->HandleInput(*this, command);
}

void dae::DigDugController::MoveRight()
{
	m_Velocity = { m_MoveSpeed, 0 };

	m_NewFacingDirection = Facing::right;
	m_DistanceMoved = 0;
}

void dae::DigDugController::MoveDown()
{
	m_Velocity = { 0, m_MoveSpeed };

	m_NewFacingDirection = Facing::down;
	m_DistanceMoved = 0;
}

void dae::DigDugController::MoveLeft()
{
	m_Velocity = { -m_MoveSpeed, 0 };

	m_NewFacingDirection = Facing::left;
	m_DistanceMoved = 0;
}

void dae::DigDugController::MoveUp()
{
	m_Velocity = { 0, -m_MoveSpeed };

	m_NewFacingDirection = Facing::up;
	m_DistanceMoved = 0;
}

void dae::DigDugController::Shoot()
{
	m_Pump->Fire(m_FacingDirection);
}

void dae::DigDugController::OnPlayerDeath()
{
	m_Lives--;
	Event playerDiedEvent;
	playerDiedEvent.type = EventType::PLAYER_DIED;
	playerDiedEvent.stringValue = m_PlayerName.c_str();
	
	NotifyObserver(playerDiedEvent);

	if (m_Lives > 0)
	{
		m_pOwner->SetWorldPosition(m_StartPos);
	}

	else
	{
		m_pAnimatorComponent->Destroy();
	}
}

void dae::DigDugController::CollisionEvent(GameObject* other)
{
	m_CurrentState->HandleCollision(*this, other);
}

void dae::DigDugController::SetTunnelManager(TunnelManagerComponent* pTunnelManager)
{
	assert(pTunnelManager != nullptr);
	m_pTunnelManager = pTunnelManager;
}

void dae::DigDugController::HandleEvent(const Event& event)
{
	switch (event.type)
	{
	case EventType::ENEMY_KILLED:
		Event scoreEvent;
		scoreEvent.type = EventType::SCORE_INCREASED;
		scoreEvent.stringValue = m_PlayerName;
		if (event.stringValue == "Pooka")
		{
			constexpr int quarterWindowHeight = 480 / 4;
			const glm::vec2 pos{ m_pOwner->GetWorldPosition() };
			if (pos.y < quarterWindowHeight * 4 && pos.y > quarterWindowHeight * 3)
			{
				scoreEvent.intValue = 500;
			}
			else if (pos.y < quarterWindowHeight * 3 && pos.y > quarterWindowHeight * 2)
			{
				scoreEvent.intValue = 400;
			}
			else if (pos.y < quarterWindowHeight * 2 && pos.y > quarterWindowHeight)
			{
				scoreEvent.intValue = 300;
			}
			else if (pos.y < quarterWindowHeight && pos.y > 0)
			{
				scoreEvent.intValue = 200;
			}
		}
		else if (event.stringValue == "Fygar")
		{
			constexpr int quarterWindowHeight = 480 / 4;
			const glm::vec2 pos{ m_pOwner->GetWorldPosition() };
			if (pos.y < quarterWindowHeight * 4 && pos.y > quarterWindowHeight * 3)
			{
				scoreEvent.intValue = 1000;
			}
			else if (pos.y < quarterWindowHeight * 3 && pos.y > quarterWindowHeight * 2)
			{
				scoreEvent.intValue = 800;
			}
			else if (pos.y < quarterWindowHeight * 2 && pos.y > quarterWindowHeight)
			{
				scoreEvent.intValue = 600;
			}
			else if (pos.y < quarterWindowHeight && pos.y > 0)
			{
				scoreEvent.intValue = 400;
			}
		}
		NotifyObserver(scoreEvent);
		break;
	}
}

void dae::DigDugController::SetSpriteSheet(std::shared_ptr<SpriteSheet> spriteSheet, const double frameTime)
{
	m_pAnimatorComponent->AddSpriteSheet(spriteSheet);
	m_pAnimatorComponent->m_FrameTime = frameTime;
}

void dae::DigDugController::DigTunnel()
{
	auto& tunnelManager = TunnelManager::GetInstance();
	auto ownerPos = m_pOwner->GetWorldPosition();
	if (!tunnelManager.InTunnel(ownerPos) == true)
	{
		tunnelManager.DigTunnel(ownerPos);
	}
}

bool dae::DigDugController::InTunnel()
{
	glm::vec2 checkPos{ m_pOwner->GetWorldPosition() };

	switch (m_FacingDirection)
	{
	case Facing::right:
		checkPos += glm::vec2{ m_CheckDistance + m_Size.x, 0 };
		break;
	case Facing::down:
		checkPos += glm::vec2{ m_CheckDistance + m_Size.y, 0 };
		break;
	case Facing::left:
		checkPos += glm::vec2{ -m_CheckDistance, 0 };
		break;
	case Facing::up:
		checkPos += glm::vec2{ 0, -m_CheckDistance };
		break;
	}

	return TunnelManager::GetInstance().InTunnel(checkPos);
}

bool dae::DigDugController::IsDoneDying()
{
	if (m_pAnimatorComponent->RenderOnce())
	{
		return true;
	}

	return false;
}

void dae::DigDugController::PlayMusic()
{
	if (m_PlayerName == "Player0")
	{
		ServiceLocator::GetSoundManager().PlayMusic();
	}
}

void dae::DigDugController::StopMusic()
{
	if (m_PlayerName == "Player0")
	{
		ServiceLocator::GetSoundManager().StopMusic();
	}
}
