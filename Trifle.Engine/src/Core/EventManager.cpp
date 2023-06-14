#include "EventManager.h"

#include "Event.h"
#include "Types.h"
#include <functional>
#include <list>
#include <unordered_map>

namespace trifle
{
    EventManager::EventManager()
    {
    }

    EventManager::~EventManager()
    {
    }

    void EventManager::AddListener(EventId eventId, std::function<void(Event &)> const &listener)
    {
        m_listeners[eventId].push_back(listener);
    }

    void EventManager::SendEvent(Event &event)
    {
        EventId type = event.GetType();

        for (auto const &listener : m_listeners[type])
        {
            listener(event);
        }
    }

    void EventManager::SendEvent(EventId eventId)
    {
        Event event(eventId);

        for (auto const &listener : m_listeners[eventId])
        {
            listener(event);
        }
    }
}