#pragma once
#include "Component.h"
namespace dae
{
	class Scene;
    class ColliderComponent final :
        public Component
    {
	public:
		ColliderComponent(GameObject* pOwner, Scene& scene);
		ColliderComponent(GameObject* pOwner, Scene& scene, const float width, const float height);
		virtual ~ColliderComponent() = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void CollisionCallback(GameObject* other);
		GameObject* GetOwner();

		const glm::vec2 GetPosition();
		glm::vec2 m_SizeOfCollider{};
    };
}
