#include "Transform.h"

void dae::Transform::SetWorldPosition(const float x, const float y)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;

	if (m_pParent != nullptr)
	{
		glm::vec2 parentWorldPosition = m_pParent->GetWorldPosition();
		glm::vec2 newLocalPosition = m_WorldPosition - parentWorldPosition;

		SetLocalPosition(newLocalPosition.x, newLocalPosition.y);
	}

	else
	{
		SetLocalPosition(x, y);
	}
}

void dae::Transform::SetWorldPosition(const glm::vec2& position)
{
	SetWorldPosition(position.x, position.y);
}

void dae::Transform::UpdateWorldPosition()
{
	m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
}

void dae::Transform::SetLocalPosition(const float x, const float y)
{
	m_LocalPosition.x = x; 
	m_LocalPosition.y = y;
}

void dae::Transform::SetLocalPosition(const glm::vec2& position)
{
	SetLocalPosition(position.x, position.y);
}

const glm::vec2 dae::Transform::GetWorldPosition() const
{
	return m_WorldPosition;
}

const glm::vec2 dae::Transform::GetLocalPosition() const
{
	return m_LocalPosition;
}

void dae::Transform::SetParent(Transform* pParent)
{
	m_pParent = pParent;
}
