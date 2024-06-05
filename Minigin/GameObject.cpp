#include "GameObject.h"
#include "ColliderComponent.h"
#include "Scene.h"
void dae::GameObject::Start(){}

void dae::GameObject::Update(const double deltaTime)
{
	if (m_IsDestroyed) return;

	for (auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}

	if (m_TransformNeedsUpdate == true)
	{
		for (auto& child : m_pChildren)
		{
			child->SetPositionDirty();
		}
		RecalculateTransform();
	}
}

void dae::GameObject::FixedUpdate(const double fixedDeltaTime)
{
	if (m_IsDestroyed) return;

	for (auto& component : m_pComponents)
	{
		component->FixedUpdate(fixedDeltaTime);
	}
}

void dae::GameObject::Render() const
{
	if (m_IsDestroyed) return;

	for (auto& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetLocalPosition(const float x, const float y)
{
	m_Transform.SetLocalPosition(x, y);
	SetPositionDirty();
}

void dae::GameObject::SetLocalPosition(const glm::vec2& pos)
{
	m_Transform.SetLocalPosition(pos);
	SetPositionDirty();
}

void dae::GameObject::SetPositionDirty()
{
	m_TransformNeedsUpdate = true;
}

void dae::GameObject::SetWorldPosition(const float x, const float y)
{
	m_Transform.SetWorldPosition(x, y);
	SetPositionDirty();
}

void dae::GameObject::SetWorldPosition(const glm::vec2& worldPosition)
{
	SetWorldPosition(worldPosition.x, worldPosition.y);
}

const glm::vec2 dae::GameObject::GetLocalPosition() const
{
	return m_Transform.GetLocalPosition();
}

const glm::vec2 dae::GameObject::GetWorldPosition() const
{
	if (m_pParent != nullptr)
		return m_pParent->GetWorldPosition() + m_Transform.GetLocalPosition();
	return m_Transform.GetLocalPosition();
}

void dae::GameObject::CollisionEvent(GameObject* other)
{
	for (auto& component : m_pComponents)
	{
		component->CollisionEvent(other);
	}
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> component)
{
	m_pComponents.emplace_back(std::move(component));
}

void dae::GameObject::AddCollider(Scene& scene)
{
	std::shared_ptr<ColliderComponent> collider = std::make_shared<ColliderComponent>(this);
	m_pCollider = collider;

	scene.AddCollider(collider);
}

void dae::GameObject::RemoveComponent()
{
	for (auto& component : m_pComponents)
	{
		if (component->m_IsDestroyed)
		{
			m_pComponents.erase(remove(m_pComponents.begin(), m_pComponents.end(), component), m_pComponents.end());
			break;
		}
	}
}

void dae::GameObject::Destroy()
{
	for (auto& component : m_pComponents)
	{
		component->Destroy();
	}
	for (auto& children : m_pChildren)
	{
		children->SetParent(nullptr);
	}

	m_IsDestroyed = true;
}

void dae::GameObject::SetParent(GameObject* pParentObject, const bool worldPositionStays)
{
	if (IsChild(pParentObject) || pParentObject == this || m_pParent == pParentObject)
		return;
	if (pParentObject == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
		m_Transform.SetParent(nullptr);
	}

	else
	{
		if (worldPositionStays) SetLocalPosition(GetWorldPosition() - pParentObject->GetWorldPosition());
		else SetLocalPosition({ 0, 0 });
		SetPositionDirty();
	}
	if (m_pParent) m_pParent->RemoveChild(this);
	m_pParent = pParentObject;
	if (m_pParent)
	{
		m_pParent->AddChild(this);
		m_Transform.SetParent(&pParentObject->m_Transform);
	}
}

dae::GameObject* dae::GameObject::GetChildAt(const size_t index) {
	if (m_pChildren.empty()) return nullptr;
	if (index < 0) return m_pChildren[0];
	if (index >= m_pChildren.size()) return m_pChildren.back();

	return m_pChildren[index];
}

bool dae::GameObject::IsChild(GameObject* pParent)
{
	if (m_pParent == nullptr) return false;
	return pParent == m_pParent;
}

void dae::GameObject::RemoveChild(GameObject* pChildObject)
{
	if (pChildObject == nullptr) return;

	m_pChildren.erase(remove(m_pChildren.begin(), m_pChildren.end(), pChildObject), m_pChildren.end());
}

void dae::GameObject::AddChild(GameObject* pChildObject) 
{
	if (pChildObject == this) return;
	if (pChildObject == m_pParent) return;

	m_pChildren.emplace_back(pChildObject);
}

void dae::GameObject::RecalculateTransform()
{
	if(m_pParent)
		m_Transform.UpdateWorldPosition();

	m_TransformNeedsUpdate = false;
}

void dae::GameObject::SnapToGrid() 
{
	const glm::vec2 currentPos{ GetWorldPosition() };

	glm::vec2 snappedPos{};
	snappedPos.x = std::round(currentPos.x / 16.0f) * 16.0f;
	snappedPos.y = std::round(currentPos.y / 16.0f) * 16.0f;
	SetWorldPosition(snappedPos);
}