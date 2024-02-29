#pragma once
#include "Component.h"
namespace dae
{
	class RotatorComponent :
		public Component
	{
	public:
		void Update(const double deltaTime) override;
		glm::vec2 GetNewPosition() const { return m_CalculatedPos; }

		RotatorComponent(GameObject* owner, const glm::vec3 centre, const float radius = 5.f, const float speed = 1.f);
		virtual ~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

	private:
		const glm::vec2 m_Centre{};
		const float m_RotationSpeed{};
		const float m_RotationRadius{};
		float m_Angle{};
		glm::vec2 m_CalculatedPos{};
	};
}
