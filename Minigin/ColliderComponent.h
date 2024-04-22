#pragma once
#include "Component.h"
namespace dae
{
    class ColliderComponent final :
        public Component
    {
	public:
		void FixedUpdate(const double fixedTimeStep) override;

		ColliderComponent(GameObject* pOwner);
		ColliderComponent(GameObject* pOwner, const float width, const float height);
		virtual ~ColliderComponent() = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

	private:
		glm::vec2 m_SizeOfCollider{};
    };
}
