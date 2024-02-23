#include "Component.h"
#include <stdexcept>

dae::Component::~Component() = default;

void dae::Component::Start() {}

void dae::Component::Render() const
{

}

void dae::Component::Update(const double) {}

void dae::Component::FixedUpdate(const double) {}

void dae::Component::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}