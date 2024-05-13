#include "DigDugState.h"

dae::NormalState* dae::NormalState::Update(DigDugController&, const double deltaTime)
{
	return nullptr;
}

void dae::NormalState::OnEnter(DigDugController& digDug)
{
};

void dae::NormalState::OnExit(DigDugController& digDug) 
{
};

void dae::NormalState::HandleInput(DigDugController& digDug) 
{
};