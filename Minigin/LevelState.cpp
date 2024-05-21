#include "LevelState.h"
#include "EventObserver.h"
using namespace dae;
LevelState::LevelState()
{
	EventObserver::GetInstance().AddListener(this);
}
