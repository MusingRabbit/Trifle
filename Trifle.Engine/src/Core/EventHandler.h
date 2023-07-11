#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "EventRegister.h"

namespace trifle
{

class EventHandler
{
  private:
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
};
} // namespace trifle

#endif // !EVENTHANDLER_H
