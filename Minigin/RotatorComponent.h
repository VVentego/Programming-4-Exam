#ifndef ROTATORCOMPONENT
#define ROTATORCOMPONENT
#include "Component.h"
#include "GameObject.h"

namespace dae
{
	class RotatorComponent :
		public Component
	{
	public:
		void Update(const double deltaTime) override;

		RotatorComponent(GameObject* owner, const glm::vec3 centre, const float radius = 5.f, const float speed = 1.f);
		virtual ~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

	private:
		glm::vec2 m_Centre{};
		float m_RotationSpeed{};
		float m_RotationRadius{};
		float m_Angle{};
		glm::vec2 m_CalculatedPos{};
	};
}

#endif // !ROTATORCOMPONENT