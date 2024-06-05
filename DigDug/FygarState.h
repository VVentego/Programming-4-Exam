#ifndef FYGARSTATE
#define FYGARSTATE
#include "FygarBehavior.h"

using namespace dae;
class FygarState
{
	FygarState() = default;
	virtual ~FygarState() = default;
	FygarState(const FygarState& other) = delete;
	FygarState(FygarState&& other) = delete;
	FygarState& operator=(const FygarState& other) = delete;
	FygarState& operator=(FygarState&& other) = delete;

	virtual FygarState* Update(FygarBehavior&, const double) { return nullptr; }

	virtual void OnEnter(FygarBehavior&) = 0;
	virtual void OnExit(FygarBehavior&) = 0;
	virtual void HandleInput(FygarBehavior&, Command*) = 0;
	virtual void HandleCollision(FygarBehavior&, GameObject*) = 0;
};

#endif // !FYGARSTATE
