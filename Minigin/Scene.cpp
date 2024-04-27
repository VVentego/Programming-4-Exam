#include "Scene.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), std::move(object)), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void dae::Scene::AddObserver(std::shared_ptr<PlayerObserver> observer)
{
	m_observers.emplace_back(std::move(observer));
}

void dae::Scene::RemoveObserver(std::shared_ptr<PlayerObserver> observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), std::move(observer)), m_observers.end());
}

void Scene::Update(const double deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::FixedUpdate(const double fixedTimeStep)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTimeStep);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void dae::Scene::Destroy()
{
	for (auto& object : m_objects)
	{
		if (object->m_IsDestroyed)
		{
			Remove(std::move(object));
			return;
		}

		object->RemoveComponent();
	}
}

void dae::Scene::AddCollider(ColliderComponent* pCollider) 
{
	m_pColliders.emplace_back(pCollider);
}

void dae::Scene::UpdateCollisions() const
{
	for (ColliderComponent* collider : m_pColliders)
	{
		for (ColliderComponent* otherCollider : m_pColliders)
		{
			if (collider == otherCollider)
			{
				continue;
			}

			const glm::vec2 colliderPosition{ collider->GetPosition() };
			const glm::vec2 otherColliderPosition{ otherCollider->GetPosition() };

			// If one rectangle is on left side of the other
			if ((colliderPosition.x + collider->m_SizeOfCollider.x) < otherColliderPosition.x || (otherColliderPosition.x + otherCollider->m_SizeOfCollider.x) < colliderPosition.x)
			{
				continue;
			}

			// If one rectangle is under the other
			if (colliderPosition.y > (otherColliderPosition.y + otherCollider->m_SizeOfCollider.y) || otherColliderPosition.y > (colliderPosition.y + collider->m_SizeOfCollider.y))
			{
				continue;
			}

			collider->CollisionCallback(otherCollider->GetOwner());
		}
	}
}

