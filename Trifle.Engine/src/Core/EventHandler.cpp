#include "EventHandler.h"

namespace tfl
{
    EventHandler::EventHandler()
    {
        m_register = nullptr;
    }

    EventHandler::EventHandler(const EventHandler& rhs)
    {
        m_id = rhs.m_id;
        m_register = rhs.m_register;
    }
    
    EventHandler::EventHandler(std::shared_ptr<IEventRegister> evtRegister)
    {
        m_register = evtRegister;
        m_id = m_register->GetNewEventId();
    }

    EventHandler::~EventHandler()
    {
    }

    void EventHandler::Init(std::shared_ptr<IEventRegister> evtRegister)
    {
        m_register = evtRegister;

        if (m_id == 0)
        {
            m_id = m_register->GetNewEventId();
        }
    }

    EventId EventHandler::GetEventId() const
    {
        return m_id;
    }

    void EventHandler::SwapListeners(const EventHandler& rhs)
    {
        m_register->SwapEventListeners(m_id, rhs.m_id);
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

    bool tfl::EventHandler::HasEventRegister()
    {
        return m_register != nullptr;
    }

    template<typename T>
    void EventHandler::Subscribe(std::function<void(EventArgs&)> const& listener)
    {
        m_register->AddListener(m_id, listener);
    }
}