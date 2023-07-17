#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "IEventRegister.h"
#include <list>
#include <unordered_map>
#include <limits.h>
#include <set>

namespace tfl
{

class EventRegister : public IEventRegister
{
  private:
    std::unordered_map<EventId, std::list<std::function<void(EventArgs&)>>> m_listeners;
    std::set<unsigned int> m_distributedIds;
    unsigned int m_lastTouchedId;

  public:
    static unsigned int MAX_EVENTHANDLERS;

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

    bool IsEmpty();
};

} // namespace tfl

#endif // !EVENTMANAGER_H
