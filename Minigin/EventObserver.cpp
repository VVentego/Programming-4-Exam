#include "EventObserver.h"
#include "Component.h"
using namespace dae;

EventObserver::~EventObserver()
{
	m_Running = false;
	cv.notify_one();

	if (m_EventsThread.joinable())
	{
		m_EventsThread.join();
	}
}

void EventObserver::Notify(const Event& event)
{
	std::unique_lock<std::mutex> lock(mutex);
	m_Events.push(event);

	cv.notify_one();
}

void EventObserver::RemoveListener(EventListener* listener)
{
	m_pListeners.erase(remove(m_pListeners.begin(), m_pListeners.end(), listener), m_pListeners.end());
}

EventObserver::EventObserver()
{
	m_EventsThread = std::jthread(&EventObserver::BroadcastToListeners, this);
}

void EventObserver::BroadcastToListeners()
{
	while (m_Running)
	{
		std::unique_lock<std::mutex> lock(mutex);
		cv.wait(lock, [this] { return !m_Events.empty() || !m_Running; });

		if (!m_Running && m_Events.empty())
		{
			break;
		}

		Event event = m_Events.front();
		m_Events.pop();

		lock.unlock();

		for (EventListener* handler : m_pListeners)
		{
			handler->HandleEvent(event);
		}
	}
}