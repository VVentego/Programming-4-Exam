#include "RotatorComponent.h"

dae::RotatorComponent::RotatorComponent(GameObject* owner, const glm::vec3 centre, const float radius, const float speed) :
    Component::Component(owner),
    m_Centre{ centre }, m_RotationRadius{ radius }, m_RotationSpeed{ speed } 
{
}

void dae::RotatorComponent::Update(const double deltaTime)
{
    m_Angle += m_RotationSpeed * static_cast<float>(deltaTime);

    // Calculate new position based on angle and radius
    glm::vec2 newPosition{};
    newPosition.x = m_Centre.x + m_RotationRadius * cos(m_Angle);
    newPosition.y = m_Centre.y + m_RotationRadius * sin(m_Angle);

    m_CalculatedPos = newPosition;
}
