#pragma once
#include "Component.h"
namespace dae
{
	class Scene;
    class ColliderComponent final :
        public Component
    {
	public:
		ColliderComponent(GameObject* pOwner);
		ColliderComponent(GameObject* pOwner, const float width, const float height);
		virtual ~ColliderComponent() = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void UpdateColliderSize(const glm::vec2 newSize);
		void CollisionCallback(GameObject* other);
		GameObject* GetOwner();

		const glm::vec2 GetPosition();
		glm::vec2 m_SizeOfCollider{};
    };
}
