#ifndef COMPONENT
#define COMPONENT
#include <memory>
#include "GameObject.h"
#include "PlayerObserver.h"
#include "../Minigin/ServiceLocator.h"

namespace dae
{
	class EventListener 
	{
	public:
		virtual ~EventListener() = default;
		virtual void HandleEvent(const Event& event) = 0;
	};

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

		virtual void AddObserver(std::shared_ptr<PlayerObserver> observer);
		virtual void CollisionEvent(GameObject*) {};

	protected:
		virtual void NotifyObservers(Event event);
		virtual void RemoveObserver(std::weak_ptr<PlayerObserver> observer);

		virtual void RemoveAllObservers();

		GameObject* m_pOwner{};
		std::vector<std::weak_ptr<PlayerObserver>> m_pObservers;
	};
}

#endif