#include "FygarPlayerController.h"
#include "FygarPlayerState.h"
#include "PumpBehaviorComponent.h"

dae::FygarPlayerController::FygarPlayerController(GameObject* pOwner, FygarBreathComponent* breath) :
	FygarBehavior(pOwner, breath), m_CurrentState{ new FygarPlayerNormalState }
{
}

dae::FygarPlayerController::~FygarPlayerController()
{
	if (m_CurrentState != nullptr)
	{
		delete m_CurrentState;
		m_CurrentState = nullptr;
	}

	ServiceLocator::GetInputManager().RemovePlayer2();
}

void dae::FygarPlayerController::Update(const double deltaTime)
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

void dae::FygarPlayerController::HandleInput(Command* command)
{
	m_CurrentState->HandleInput(*this, command);
}

void dae::FygarPlayerController::MoveRight()
{
	m_Velocity = { m_MoveSpeed, 0 };

	m_NewFacingDirection = Facing::right;
	m_DistanceMoved = 0;
}

void dae::FygarPlayerController::MoveDown()
{
	m_Velocity = { 0, m_MoveSpeed };

	m_NewFacingDirection = Facing::down;
	m_DistanceMoved = 0;
}

void dae::FygarPlayerController::MoveLeft()
{
	m_Velocity = { -m_MoveSpeed, 0 };

	m_NewFacingDirection = Facing::left;
	m_DistanceMoved = 0;
}

void dae::FygarPlayerController::MoveUp()
{
	m_Velocity = { 0, -m_MoveSpeed };

	m_NewFacingDirection = Facing::up;
	m_DistanceMoved = 0;
}

void dae::FygarPlayerController::Shoot()
{
	m_BreatheFire = true;
}

void dae::FygarPlayerController::Mute()
{
	ServiceLocator::GetSoundManager().ToggleMute();
}

void dae::FygarPlayerController::Skip()
{
	Event skipEvent{};
	skipEvent.type = EventType::SKIP_LEVEL;

	NotifyObserver(skipEvent);
}

void dae::FygarPlayerController::CrushedByRock()
{
	ServiceLocator::GetSoundManager().Play(2, 100);

	Event playerDiedEvent;
	playerDiedEvent.type = EventType::PLAYER_DIED;
	playerDiedEvent.stringValue = m_PlayerName.c_str();

	NotifyObserver(playerDiedEvent);

	if (m_Lives > 0)
	{
		--m_Lives;
		Respawn();
	}

	else
	{
		m_pOwner->Destroy();
	}
}

void dae::FygarPlayerController::Die()
{
	if (m_Dead)
	{
		return;
	}

	m_Dead = true;
	ServiceLocator::GetSoundManager().Play(3, 100);
	ServiceLocator::GetSoundManager().Play(2, 100);
	m_pPump->Reset();
	Event enemyKilledEvent;

	//Notify event is passed to player and then player passes on a score gained event depending on depth
	enemyKilledEvent.type = EventType::ENEMY_KILLED;
	enemyKilledEvent.stringValue = "Fygar" + std::to_string(m_AttackingPlayerIdx);
	NotifyObserver(enemyKilledEvent);

	Event playerDiedEvent;
	playerDiedEvent.type = EventType::PLAYER_DIED;
	playerDiedEvent.stringValue = m_PlayerName.c_str();

	NotifyObserver(playerDiedEvent);

	if (m_Lives > 0)
	{
		--m_Lives;
		Respawn();
	}
	else
	{
		m_pOwner->Destroy();
	}
}

void dae::FygarPlayerController::Respawn()
{
	m_pOwner->SetWorldPosition(m_StartPos);
	m_Dead = false;
}