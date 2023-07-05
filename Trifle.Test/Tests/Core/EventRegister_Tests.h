#pragma Once

#include <gtest/gtest.h>
#include <cstdlib>
#include <functional>

#include <Core/EventRegister.h>
#include <Core/Types.h>

#include <stdexcept>

using namespace trifle;

bool AddListener_OnEventFired_0_hit = false;

void AddListener_OnEventFired_0(EventArgs& evt)
{
    AddListener_OnEventFired_0_hit = true;
}

TEST(EventRegister, GetNewEventId_Test)
{
    EventRegister eRegister;

    for (unsigned int i = 0; i < EventRegister::MAX_EVENTHANDLERS; i++)
    {
        EventId eId1 = eRegister.GetNewEventId();
        ASSERT_EQ(eId1, i);
    }
}

TEST(EventRegister, GetNewEventId_TooManyEventIds_Test)
{
    EventRegister eRegister;

    for (unsigned int i = 0; i < EventRegister::MAX_EVENTHANDLERS; i++)
    {
        EventId eId1 = eRegister.GetNewEventId();
        ASSERT_EQ(eId1, i);
    }

    ASSERT_THROW(eRegister.GetNewEventId(), std::runtime_error);
}

TEST(EventRegister, GetNewEventId_AfterRelease)
{
    EventRegister eRegister;

    for (unsigned int i = 0; i < 10; i++)
    {
        eRegister.GetNewEventId();
    }

    for (unsigned int i = 0; i > 5; i++)
    {
        eRegister.ReleaseEventId(i);
    }

    ASSERT_EQ(eRegister.GetNewEventId(), 6);
}

TEST(EventRegister, AddListener)
{
    EventRegister eRegister;
    EventId id = eRegister.GetNewEventId();

    std::function<void(EventArgs&)> func = AddListener_OnEventFired_0;

    eRegister.AddListener(id, func);
}

TEST(EventRegister, SendEvent)
{
    AddListener_OnEventFired_0_hit = false;

    EventRegister eRegister;
    EventId id = eRegister.GetNewEventId();

    std::function<void(EventArgs&)> func = AddListener_OnEventFired_0;

    eRegister.AddListener(id, func);

    eRegister.SendEvent(id);

    ASSERT_TRUE(AddListener_OnEventFired_0_hit);
}
