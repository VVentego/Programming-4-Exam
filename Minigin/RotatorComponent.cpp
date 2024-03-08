#include "RotatorComponent.h"

dae::RotatorComponent::RotatorComponent(GameObject* owner, const glm::vec3 centre, const float radius, const float speed) :
    Component::Component(owner),
    m_Centre{ centre }, m_RotationRadius{ radius }, m_RotationSpeed{ speed } 
{
}

void dae::RotatorComponent::Update(const double deltaTime)
{
    m_Angle += m_RotationSpeed * static_cast<float>(deltaTime);
    constexpr float twoPi{ 2 * static_cast<float>(M_PI) };
    if (m_Angle > twoPi) m_Angle -= twoPi;

    // Calculate new position based on angle and radius
    glm::vec2 newPosition{};
    newPosition.x = m_Centre.x + m_RotationRadius * cos(m_Angle);
    newPosition.y = m_Centre.y + m_RotationRadius * sin(m_Angle);

    m_CalculatedPos = newPosition;
    //Set local position
    m_pOwner->SetLocalPosition(m_CalculatedPos.x, m_CalculatedPos.y, 0);
}
