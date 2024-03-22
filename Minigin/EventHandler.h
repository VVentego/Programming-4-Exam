#ifndef EVENTHANDLER
#define EVENTHANDLER
#include "Component.h"
namespace dae
{
    class EventHandler :
        public Component
    {
	public:
		virtual ~EventHandler() = default;
		EventHandler(const EventHandler& other) = delete;
		EventHandler(EventHandler&& other) = delete;
		EventHandler& operator=(const EventHandler& other) = delete;
		EventHandler& operator=(EventHandler&& other) = delete;

		virtual void HandleEvent(const Event& event) = 0;
	protected:
		EventHandler(GameObject* pOwner) : Component(pOwner) {};
    };
}
#endif // !EVENTHANDLER
