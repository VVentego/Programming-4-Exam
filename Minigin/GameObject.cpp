#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start(){}

void dae::GameObject::Update(const double deltaTime)
{
	for (auto& component : m_pComponents)
	{
		component.second->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(const double fixedDeltaTime)
{
	for (auto& component : m_pComponents)
	{
		component.second->FixedUpdate(fixedDeltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (auto& component : m_pComponents)
	{
		component.second->Render();
	}
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

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

void dae::GameObject::RemoveComponent(const std::string& componentName)
{
	m_pComponents.erase(componentName);
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
