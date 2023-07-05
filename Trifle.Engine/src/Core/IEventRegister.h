#ifndef IEVENTREGISTER_H
#define IEVENTREGISTER_H

#include "EventArgs.h"
#include "Types.h"
#include <functional>

namespace trifle
{
class IEventRegister
{
  public:
    virtual EventId GetNewEventId() = 0;
    virtual void ReleaseEventId(EventId eventId) = 0;
    virtual void AddListener(EventId eventId, std::function<void(EventArgs&)> const& listener) = 0;
    virtual void SendEvent(EventArgs& args) = 0;
    virtual void SendEvent(EventId eventId) = 0;
};
} // namespace trifle

#endif // !IEVENTREGISTER_H
