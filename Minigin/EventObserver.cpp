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

void dae::EventObserver::AddListener(EventListener* eventListener)
{
	auto it = std::find(m_pListeners.begin(), m_pListeners.end(), eventListener);
	if (it == m_pListeners.end())
	{
		m_pListeners.push_back(eventListener);
	}
}

void EventObserver::RemoveListener(EventListener* listener)
{
	auto it = std::find(m_pListeners.begin(), m_pListeners.end(), listener);
	if (it != m_pListeners.end())
	{
		m_pListeners.erase(it);
	}
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
			if (handler == nullptr)
			{
				continue;
			}
			handler->HandleEvent(event);
		}
	}
}