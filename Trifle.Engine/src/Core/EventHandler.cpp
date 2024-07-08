#include "EventHandler.h"

using namespace tfl;

EventHandler::EventHandler()
{
    m_register = &EventRegister::GetInstance();
    m_id = m_register->GetNewEventId();
}

EventHandler::EventHandler(const EventHandler& rhs)
{
    m_register = rhs.m_register;
    m_id = rhs.m_id;
}

EventHandler::EventHandler(IEventRegister& eventRegister)
{
    m_register = &eventRegister;
    m_id = m_register->GetNewEventId();
}

EventHandler::~EventHandler()
{
    m_register->ReleaseEventId(m_id);
}

void EventHandler::Invoke()
{
    m_register->SendEvent(m_id);
}

void EventHandler::Invoke(std::any data)
{
    EventArgs args(m_id);
    args.SetData(data);
    m_register->SendEvent(args);
}

void EventHandler::Subscribe(const std::function<void(EventArgs&)>& listener)
{
    m_register->AddListener(m_id, listener);
}

void EventHandler::UnSubscribe()
{
    m_register->ReleaseEventId(m_id);
}

template<typename T>
void EventHandler::Subscribe(std::function<void(EventArgs&)> const& listener)
{
    m_register->AddListener(m_id, listener);
}
