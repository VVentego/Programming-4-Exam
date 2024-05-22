#ifndef THREADSAFEQUEUE
#define THREADSAFEQUEUE
#include <mutex>
#include <queue>

template<typename t>
class ThreadSafeQueue
{
public:
	void Push(t value)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		m_Queue.push(std::move(value));
		m_Condition.notify_one();
	}

    bool TryPop(t& value) {
        std::lock_guard<std::mutex> lock(m_Mutex);
        if (queue_.empty()) return false;

        value = std::move(m_Queue.front());
        m_Queue.pop();
        return true;
    }

    bool WaitPop(t& value) {
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_Condition.wait(lock, [this] { return !m_Queue.empty(); });

        value = std::move(m_Queue.front());
        m_Queue.pop();
        return true;
    }
private:
	std::queue<t> m_Queue;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
};

#endif