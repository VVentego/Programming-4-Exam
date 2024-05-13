#ifndef EVENTHANDLER
#define EVENTHANDLER
namespace dae
{
	struct Event;
    class EventHandler
    {
	public:
		virtual ~EventHandler() = default;
		EventHandler(const EventHandler& other) = delete;
		EventHandler(EventHandler&& other) = delete;
		EventHandler& operator=(const EventHandler& other) = delete;
		EventHandler& operator=(EventHandler&& other) = delete;

		virtual void HandleEvent(const Event& event) = 0;
	protected:
		EventHandler() = default;
    };
}
#endif // !EVENTHANDLER

