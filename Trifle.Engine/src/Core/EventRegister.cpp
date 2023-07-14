#include "EventRegister.h"

#include "EventArgs.h"
#include "Types.h"
#include <functional>
#include <list>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

namespace trifle
{
unsigned int EventRegister::MAX_EVENTHANDLERS = UINT_MAX;

EventRegister::EventRegister()
{
    srand(time(0));
    m_distributedIds = {};
    m_lastTouchedId = 0;
}

EventRegister::~EventRegister()
{
    m_distributedIds.clear();
}

EventId EventRegister::GetNewEventId()
{
    EventId result = m_lastTouchedId + 1;
    unsigned int startingId = result > MAX_EVENTHANDLERS ? 1 : result;
    result = startingId;
    bool isValid = false; // TODO : Put in a max loop limit.....
    bool lapped = false;

    while (!isValid)
    {
        if (m_distributedIds.find(result) == m_distributedIds.end())
        {
            isValid = true;
            break;
        }

        if (result == startingId)
        {
            if (lapped)
            {
                throw std::runtime_error("EventRegister::MAX_EVENTHANDLERS exceeded.");
            }

            lapped = true;
        }

        result = result >= MAX_EVENTHANDLERS ? 1 : result + 1;
    }

    m_distributedIds.insert(result);
    m_lastTouchedId = result;
    return result;
}

void EventRegister::ReleaseEventId(EventId eventId)
{
    if (IsEmpty())
    {
        return;
    }

    if (m_distributedIds.find(eventId) != m_distributedIds.end())
    {
        m_lastTouchedId = eventId - 1;
        m_distributedIds.erase(eventId);
    }

    if (m_listeners.find(eventId) != m_listeners.end())
    {
        m_listeners.erase(eventId);
    }
}

void EventRegister::AddListener(EventId eventId, std::function<void(EventArgs&)> const& listener)
{
    m_listeners[eventId].push_back(listener);
}

void EventRegister::SendEvent(EventArgs& args)
{
    EventId type = args.GetEventId();

    for (auto const& listener : m_listeners[type])
    {
        listener(args);
    }
}

void EventRegister::SendEvent(EventId eventId)
{
    EventArgs args(eventId);

    for (auto const& listener : m_listeners[eventId])
    {
        listener(args);
    }
}
bool EventRegister::IsEmpty()
{
    return m_distributedIds.size() < 1;
}
} // namespace trifle
