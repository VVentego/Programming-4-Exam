#include "DigDugState.h"

dae::NormalState* dae::NormalState::Update(DigDugController&, const double)
{
	return nullptr;
}

void dae::NormalState::OnEnter(DigDugController&)
{
};

void dae::NormalState::OnExit(DigDugController&) 
{
};

void dae::NormalState::HandleInput(DigDugController&) 
{
};