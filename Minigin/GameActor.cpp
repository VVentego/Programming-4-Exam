#include "GameActor.h"

GameActor::GameActor(GameObject* pControlledObject, std::unique_ptr<GameActorCommand> pActorCommand) :
	m_pPlayerObject{ pControlledObject }, m_pActorCommand{ std::move(pActorCommand) }
{
}
