#include "Transform.h"

void dae::Transform::SetWorldPosition(const float x, const float y, const float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;

	if (m_pParent != nullptr)
	{
		glm::vec3 parentWorldPosition = m_pParent->GetWorldPosition();
		glm::vec3 newLocalPosition = m_WorldPosition - parentWorldPosition;

		SetLocalPosition(newLocalPosition.x, newLocalPosition.y, newLocalPosition.z);
	}

	else
		SetLocalPosition(x, y, z);
}

void dae::Transform::SetWorldPosition(const glm::vec3& position)
{
	SetWorldPosition(position.x, position.y, position.z);
}

void dae::Transform::UpdateWorldPosition()
{
	m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x; 
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}

void dae::Transform::SetLocalPosition(const glm::vec3& position)
{
	SetLocalPosition(position.x, position.y, position.z);
}

const glm::vec3 dae::Transform::GetWorldPosition() const
{
	return m_WorldPosition;
}

const glm::vec3 dae::Transform::GetLocalPosition() const
{
	return m_LocalPosition;
}

void dae::Transform::SetParent(Transform* pParent)
{
	m_pParent = pParent;
}
