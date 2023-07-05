#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "IEventRegister.h"
#include <list>
#include <unordered_map>
#include <limits.h>
#include <queue>

namespace trifle
{

class EventRegister : public IEventRegister
{
  private:
    std::unordered_map<EventId, std::list<std::function<void(EventArgs&)>>> m_listeners;
    std::queue<unsigned int> m_availableIds;

  public:
    static const unsigned int MAX_EVENTHANDLERS = 1000000;

    static IEventRegister& GetInstance()
    {
        static EventRegister instance;
        return instance;
    }

    EventRegister();
    ~EventRegister();

    EventId GetNewEventId();
    void ReleaseEventId(EventId eventId);

    void AddListener(EventId eventId, std::function<void(EventArgs&)> const& listener);
    void SendEvent(EventArgs& args);
    void SendEvent(EventId eventId);
};
} // namespace trifle

#endif // !EVENTMANAGER_H
