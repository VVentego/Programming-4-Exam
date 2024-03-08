#ifndef COMPONENT
#define COMPONENT

#include <memory>
#include "GameObject.h"

namespace dae
{
	class Renderer;
	class GameObject;
	class Component
	{
	public:
		virtual void Update(const double deltaTime);
		virtual void FixedUpdate(const double fixedTimeStep);
		virtual void Start();
		virtual void Render() const;

		virtual void Destroy();

		Component(GameObject* owner);
		virtual ~Component();
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
		bool m_IsDestroyed{};

	protected:
		glm::vec3 m_Position{};
		GameObject* m_pOwner{};
	};
}

#endif