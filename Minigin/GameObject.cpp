#include "GameObject.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start(){}

void dae::GameObject::Update(const double deltaTime)
{
	if (m_IsDestroyed) return;

	for (auto& component : m_pComponents)
	{
		component.second->Update(deltaTime);
	}

	if (m_NeedsUpdate == true && !m_pChildren.empty())
		for (GameObject* child : m_pChildren)
		{
			glm::vec3 position{ GetPosition() };
			child->SetPosition(position.x + child->m_LocalPosition.x, position.y + child->m_LocalPosition.y);
			m_NeedsUpdate = false;
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

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);

	for (auto& component : m_pComponents)
	{
		component.second->SetPosition(x, y);
	}

	m_NeedsUpdate = true;
}

void dae::GameObject::AddComponent(const std::string& componentName, std::shared_ptr<Component> component)
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
	//If self, return
	if (pParentObject == this) return;
	//Remove parent
	if (pParentObject == nullptr)
	{
		m_pParent = nullptr;
		m_LocalPosition = glm::vec3{ 0, 0, 0 };
		return;
	}

	if (m_pParent != nullptr) m_pParent->RemoveChild(this);

	m_pParent = pParentObject;
	pParentObject->AddChildToVector(this);

	const glm::vec3 parentTransform{ pParentObject->GetPosition() };
	if (worldPositionStays)
	{
		glm::vec3 localPosition{ m_transform.GetPosition() - parentTransform };
		m_LocalPosition = localPosition;
		glm::vec3 newWorldPos{ parentTransform + localPosition };

		SetPosition(newWorldPos.x, newWorldPos.y);
	}

	if (worldPositionStays == false)
	{
		SetPosition(parentTransform.x, parentTransform.y);
	}
}

dae::GameObject* dae::GameObject::GetChildAt(const int index) {
	if (m_pChildren.empty()) return nullptr;
	if (index < 0) return m_pChildren[0];
	if (index >= m_pChildren.size()) return m_pChildren.back();

	return m_pChildren[index];
}

void dae::GameObject::RemoveChild(GameObject* pChildObject)
{
	if (pChildObject == nullptr) return;

	m_pChildren.erase(remove(m_pChildren.begin(), m_pChildren.end(), pChildObject), m_pChildren.end());
	pChildObject->SetParent(nullptr);
}

void dae::GameObject::AddChild(GameObject* pChildObject, const bool worldPositionStays) 
{
	if (pChildObject == this || pChildObject == nullptr) return;
	if (pChildObject == m_pParent) return;

	 pChildObject->SetParent(this, worldPositionStays);
}
