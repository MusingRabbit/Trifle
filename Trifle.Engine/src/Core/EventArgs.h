#ifndef EVENTARGS_H
#define EVENTARGS_H

#include "Types.h"
#include <any>
#include <unordered_map>
#include <iostream>

namespace tfl
{
class EventArgs
{
  private:
    EventId m_eventId;
    std::any m_data;

  public:
    EventArgs() = delete;

    explicit EventArgs(EventId type) : m_eventId(type)
    {
        m_data = {};
    }

    void SetData(std::any data)
    {
        m_data = data;
    }

    template <typename T>
    T& GetData()
    {
        return (T&)m_data;
    }

    EventId GetEventId() const
    {
        return m_eventId;
    }
};

} // namespace tfl

#endif // DEBUG