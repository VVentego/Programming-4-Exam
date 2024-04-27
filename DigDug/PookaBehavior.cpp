#include "PookaBehavior.h"
#include "PumpBehaviorComponent.h"

dae::PookaBehavior::PookaBehavior(GameObject* pOwner) :
	Component(pOwner)
{
}

void dae::PookaBehavior::CollisionEvent(GameObject* other)
{
	auto collidedObject = other->GetComponent<PumpBehaviorComponent>();
	if (collidedObject != nullptr && collidedObject->IsActive())
	{
		ServiceLocator::GetInstance().GetSoundManager().Play(1, 50);
	}
}
