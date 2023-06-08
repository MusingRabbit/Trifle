#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Event.h"
#include "Types.h"
#include <functional>
#include <list>
#include <unordered_map>

class EventManager
{
private:
    std::unordered_map<EventId, std::list<std::function<void(Event&)>>> m_listeners;
public:
    EventManager();
    ~EventManager();

    void AddListener(EventId eventId, std::function<void(Event&)> const& listener);
    void SendEvent(const Event& event);
    void SendEvent(EventId eventId);
};



#endif // !EVENTMANAGER_H
