#pragma once

#include <gtest/gtest.h>
#include <cstdlib>
#include <functional>
#include <limits>

#include <trifle.h>

#include <stdexcept>

using namespace tfl;

bool AddListener_OnEventFired_0_hit = false;

void AddListener_OnEventFired_0(EventArgs& evt)
{
    AddListener_OnEventFired_0_hit = true;
}

TEST(EventRegister, GetNewEventId_Test)
{
    EventRegister eRegister;

    EventRegister::MAX_EVENTHANDLERS = 10;

    for (unsigned int i = 0; i < EventRegister::MAX_EVENTHANDLERS; i++)
    {
        EventId eId1 = eRegister.GetNewEventId();
        ASSERT_EQ(eId1, i + 1);
    }

    EventRegister::MAX_EVENTHANDLERS = UINT_MAX;
}

TEST(EventRegister, GetNewEventId_TooManyEventIds_Test)
{
    EventRegister eRegister;

    EventRegister::MAX_EVENTHANDLERS = 10;

    for (unsigned int i = 0; i < EventRegister::MAX_EVENTHANDLERS; i++)
    {
        EventId eId1 = eRegister.GetNewEventId();
        ASSERT_EQ(eId1, i + 1);
    }

    ASSERT_THROW(eRegister.GetNewEventId(), std::runtime_error);

    EventRegister::MAX_EVENTHANDLERS = UINT_MAX;
}

TEST(EventRegister, GetNewEventId_AfterRelease)
{
    EventRegister eRegister;

    for (unsigned int i = 0; i < 10; i++)
    {
        eRegister.GetNewEventId();
    }

    eRegister.ReleaseEventId(5);

    EventId newId = eRegister.GetNewEventId();

    ASSERT_EQ(newId, 5);
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
