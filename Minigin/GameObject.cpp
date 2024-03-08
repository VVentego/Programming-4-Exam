#include "GameObject.h"
void dae::GameObject::Start(){}

void dae::GameObject::Update(const double deltaTime)
{
	if (m_IsDestroyed) return;

	for (auto& component : m_pComponents)
	{
		component.second->Update(deltaTime);
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
		component.second->FixedUpdate(fixedDeltaTime);
	}
}

void dae::GameObject::Render() const
{
	if (m_IsDestroyed) return;

	for (auto& component : m_pComponents)
	{
		component.second->Render();
	}
}

void dae::GameObject::SetLocalPosition(const float x, const float y, const float z)
{
	m_Transform.SetLocalPosition(x, y, z);
	SetPositionDirty();
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_Transform.SetLocalPosition(pos);
	SetPositionDirty();
}

void dae::GameObject::SetPositionDirty()
{
	m_TransformNeedsUpdate = true;
}

void dae::GameObject::SetWorldPosition(const float x, const float y, const float z)
{
	m_Transform.SetWorldPosition(x, y, z);
	SetPositionDirty();
}

void dae::GameObject::SetWorldPosition(const glm::vec3& worldPosition)
{
	SetWorldPosition(worldPosition.x, worldPosition.y, worldPosition.z);
}

const glm::vec3 dae::GameObject::GetWorldPosition() const
{
	if (m_pParent != nullptr)
		return m_pParent->GetWorldPosition() + m_Transform.GetLocalPosition();
	return m_Transform.GetLocalPosition();
}

void dae::GameObject::AddComponent(const std::string& componentName, std::unique_ptr<Component> component)
{
	m_pComponents.emplace(componentName, std::move(component));
}

void dae::GameObject::DestroyComponent(const std::string& componentName)
{
	GetComponent(componentName)->Destroy();
}

void dae::GameObject::RemoveComponent()
{
	std::vector<std::string> componentsToRemove;

	for (auto& component : m_pComponents)
	{
		if (component.second->m_IsDestroyed)
			componentsToRemove.emplace_back(component.first);
	}

	for (auto& componentName : componentsToRemove)
	{
		m_pComponents.erase(componentName);
	}
}

std::shared_ptr<dae::Component> dae::GameObject::GetComponent(const std::string& componentName)
{
	auto it = m_pComponents.find(componentName);
	if (it != m_pComponents.end())
	{
		return it->second;
	}

	return nullptr;
}

bool dae::GameObject::ComponentExists(const std::string& componentName) const
{
	auto it = m_pComponents.find(componentName);
	if (it != m_pComponents.end())
	{
		return true;
	}

	return false;
}

void dae::GameObject::Destroy()
{
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
		else SetLocalPosition({ 0, 0,0 });
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
