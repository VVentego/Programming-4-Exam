#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start(){}

void dae::GameObject::Update(const double deltaTime)
{
	if (m_IsDestroyed) return;

	for (auto& component : m_pComponents)
	{
		component.second->Update(deltaTime);
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
	
	for (auto component : m_pComponents)
	{
		component.second->SetPosition(x, y);
	}
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
