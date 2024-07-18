#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "EventRegister.h"
#include <any>

namespace tfl
{
class EventHandler
{
  private:
  protected:
    EventId m_id;
    std::shared_ptr<IEventRegister> m_register = nullptr;

  public:
    EventHandler();

    EventHandler(const EventHandler& rhs);

    EventHandler(std::shared_ptr<IEventRegister> evtRegister);

    ~EventHandler();

    void Init(std::shared_ptr<IEventRegister> evtRegister);
    
    EventId GetEventId() const;

    void SwapListeners(const EventHandler& rhs);

    void Invoke();
    void Invoke(std::any data);
    void Subscribe(std::function<void(EventArgs&)> const& listener);
    void UnSubscribe();

    bool HasEventRegister();

    template<typename T>
    void Invoke(T data)
    {
      EventArgs args(m_id);
      args.SetData(data);
      m_register->SendEvent(args);
    }

    template<typename T>
    void Subscribe(std::function<void(EventArgs&)> const& listener);
};


} // namespace tfl

#endif // !EVENTHANDLER_H
