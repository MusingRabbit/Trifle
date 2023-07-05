#include "EventRegister.h"

#include "EventArgs.h"
#include "Types.h"
#include <functional>
#include <list>
#include <unordered_map>
#include <stdexcept>

namespace trifle
{
EventRegister::EventRegister()
{
    m_availableIds = {};

    for (unsigned int i = 0; i < MAX_EVENTHANDLERS; i++)
    {
        m_availableIds.push(i);
    }
}

EventRegister::~EventRegister()
{
}

EventId EventRegister::GetNewEventId()
{
    if (m_availableIds.empty())
    {
        throw std::runtime_error("Too many event handlers have been created.");
    }

    EventId result = m_availableIds.front();
    m_availableIds.pop();

    return result;
}

void EventRegister::ReleaseEventId(EventId eventId)
{
    m_availableIds.push(eventId);
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
} // namespace trifle
