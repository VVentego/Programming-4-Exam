#include "Scene.h"
#include <algorithm>
#include "LevelState.h"
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
	object.reset();
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
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

void dae::Scene::AddCollider(std::shared_ptr<ColliderComponent> pCollider) 
{
	m_pColliders.emplace_back(std::weak_ptr<ColliderComponent>(pCollider));
}

void dae::Scene::UpdateCollisions() const
{
	m_pColliders.erase(
		std::remove_if(m_pColliders.begin(), m_pColliders.end(),
			[](const std::weak_ptr<ColliderComponent>& collider) {
				return collider.expired();
			}),
		m_pColliders.end());

	for (std::weak_ptr<ColliderComponent> collider : m_pColliders)
	{
		if (collider.expired())
		{
			//remove collider from m_pColliders
			continue;
		}
		for (std::weak_ptr<ColliderComponent> otherCollider : m_pColliders)
		{

			if (collider.lock() == otherCollider.lock())
			{
				continue;
			}

			const glm::vec2 colliderPosition{ collider.lock()->GetPosition()};
			const glm::vec2 otherColliderPosition{ otherCollider.lock()->GetPosition() };

			// If one rectangle is on left side of the other
			if ((colliderPosition.x + collider.lock()->m_SizeOfCollider.x) < otherColliderPosition.x || (otherColliderPosition.x + otherCollider.lock()->m_SizeOfCollider.x) < colliderPosition.x)
			{
				continue;
			}

			// If one rectangle is under the other
			if (colliderPosition.y > (otherColliderPosition.y + otherCollider.lock()->m_SizeOfCollider.y) || otherColliderPosition.y > (colliderPosition.y + collider.lock()->m_SizeOfCollider.y))
			{
				continue;
			}

			collider.lock()->CollisionCallback(otherCollider.lock()->GetOwner());
		}
	}
}

