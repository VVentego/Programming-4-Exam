#ifndef PLAYEROBSERVER
#define PLAYEROBSERVER
#include <vector>
#include <memory>

namespace dae
{
    //EventHandler
    class EventHandler;

    enum class EventArgType {
        INT,
        FLOAT,
        STRING,
    };

    //Don't use a union, use templates.
    union EventArg {
        int intValue{};
        float floatValue;
        const char* stringValue;

        EventArg() {}
        ~EventArg() {}
    };

    enum class EventType {
        SCORE_INCREASED,
        PLAYER_DIED
    };
    struct Event {
        static const uint8_t MAX_ARGS = 3;
        EventType m_type;
        uint8_t m_numArgs;
        EventArg m_args[MAX_ARGS];
    };

    //Too much coupling, it should only observe and broadcast
    class PlayerObserver
    {
        friend class Component;
    public:
        PlayerObserver() = default;
        virtual ~PlayerObserver() = default;
        PlayerObserver(const PlayerObserver& other) = delete;
        PlayerObserver(PlayerObserver&& other) = delete;
        PlayerObserver& operator=(const PlayerObserver& other) = delete;
        PlayerObserver& operator=(PlayerObserver&& other) = delete;

        virtual void OnNotify(const Event& event);
        virtual void AddSubject(Component* subject);
        virtual void RemoveSubject(Component* subject);
        virtual void BroadcastToHandlers(const Event& event);
        virtual void AddHandler(EventHandler* eventHandler) { m_pEventHandlers.emplace_back(eventHandler); }

    private:
        const int m_WinnerScore{ 500 };
        float m_TotalScore{};
        std::vector<Component*> m_pSubjects;
        std::vector<EventHandler*> m_pEventHandlers;
    };
}

#endif // !PLAYEROBSERVER