#ifndef COMPONENT
#define COMPONENT
#include <memory>
#include "GameObject.h"
#include "EventObserver.h"
#include "ServiceLocator.h"

namespace dae
{
	struct Rectf
	{
		float x{};
		float y{};
		float w{};
		float h{};
	};

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

		virtual void CollisionEvent(GameObject*) {};

	protected:
		virtual void NotifyObserver(Event event);

		GameObject* m_pOwner{};
		std::vector<std::weak_ptr<EventObserver>> m_pObservers;
	};
}

#endif