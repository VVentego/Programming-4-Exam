#ifndef EVENTOBSERVER
#define EVENTOBSERVER
#include "Singleton.h"
#include <vector>
#include <memory>
#include <string>
#include <queue>
#include <mutex>
#include "EventListener.h"

namespace dae
{
    class Component;

    class EventObserver final : public Singleton<EventObserver>
    {
	public:
		~EventObserver();
		EventObserver(const EventObserver& other) = delete;
		EventObserver(EventObserver&& other) = delete;
		EventObserver& operator=(const EventObserver& other) = delete;
		EventObserver& operator=(EventObserver&& other) = delete;

        void Notify(const Event& event);
        void AddListener(EventListener* eventListener) { m_pListeners.push_back(eventListener); }
        void RemoveListener(EventListener* listener);

	private:
		friend class Singleton;
		EventObserver();

        void BroadcastToListeners();

        std::vector<EventListener*> m_pListeners;
        std::queue<Event> m_Events;
        std::jthread m_EventsThread;
        std::condition_variable cv{};
        std::mutex mutex;
        bool m_Running{ true };
    };
}
#endif // !EVENTOBSERVER

