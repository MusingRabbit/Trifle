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
    IEventRegister* m_register;

  public:
    EventHandler();
    EventHandler(const EventHandler& rhs);
    EventHandler(IEventRegister& eventRegister);
    ~EventHandler();

    void Invoke();
    void Invoke(std::any data);
    void Subscribe(std::function<void(EventArgs&)> const& listener);
    void UnSubscribe();

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
