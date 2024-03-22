#ifndef COMPONENT
#define COMPONENT
#include <memory>
#include "GameObject.h"
#include "PlayerObserver.h"

namespace dae
{
	class Renderer;
	class PlayerObserver;
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

	protected:
		virtual void NotifyObservers(Event event);
		virtual void RemoveObserver(std::weak_ptr<PlayerObserver> observer);

		virtual void RemoveAllObservers();

		glm::vec3 m_Position{};
		GameObject* m_pOwner{};
		std::vector<std::weak_ptr<PlayerObserver>> m_pObservers;
	};
}

#endif