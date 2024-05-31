#ifndef EVENTLISTENER
#define EVENTLISTENER
#include <string>

enum class EventType {
    SCORE_INCREASED,
    PLAYER_DIED,
    ENEMY_KILLED,
    LOAD_LEVEL
};

struct Event {
    EventType type;
    int intValue;
    float floatValue;
    std::string stringValue;
};

class EventListener
{
public:
	virtual ~EventListener() = default;
	virtual void HandleEvent(const Event& event) = 0;
};
#endif // !EVENTLISTENER