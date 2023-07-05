#include "EventHandler.h"

namespace trifle
{
EventHandler::EventHandler() : m_register(EventRegister::GetInstance())
{
    m_id = m_register.GetNewEventId();
}

EventHandler::EventHandler(IEventRegister& eventRegister) : m_register(eventRegister)
{
    m_id = m_register.GetNewEventId();
}

EventHandler::~EventHandler()
{
    m_register.ReleaseEventId(m_id);
}

void EventHandler::Invoke()
{
    m_register.SendEvent(m_id);
}

void EventHandler::Invoke(std::any data)
{
    EventArgs args(m_id);
    args.SetData(data);
    m_register.SendEvent(args);
}

void EventHandler::Subscribe(std::function<void(EventArgs&)> const& listener)
{
    m_register.AddListener(m_id, listener);
}
} // namespace trifle
