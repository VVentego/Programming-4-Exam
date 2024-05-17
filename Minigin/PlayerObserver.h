#ifndef PLAYEROBSERVER
#define PLAYEROBSERVER
#include <vector>
#include <memory>
#include <string>

namespace dae
{
    //EventHandler
    class EventListener;
    class Component;

    enum class EventType {
        SCORE_INCREASED,
        PLAYER_DIED,
        ENEMY_KILLED
    };

    struct Event {
        EventType type;
        int intValue;
        float floatValue;
        std::string stringValue;
    };

    //Too much coupling, it should only observe and broadcast
    class PlayerObserver
    {
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
        virtual void BroadcastToListeners(const Event& event);
        virtual void AddListener(EventListener* eventListener) { m_pListeners.emplace_back(eventListener); }

    private:
        std::vector<EventListener*> m_pListeners;
        std::vector<Component*> m_pSubjects;
    };
}

#endif // !PLAYEROBSERVER