#pragma once

#include <gtest/gtest.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <trifle.h>

using namespace tfl;

void CreateEntities(EntityRegister& manager, unsigned int entityCount)
{
    for (unsigned int i = 0; i < entityCount; i++)
    {
        manager.CreateEntity();
    }
}

TEST(EntityRegister, CreateEntity_Test)
{
    EntityRegister manager;
    CreateEntities(manager, 30);

    ASSERT_EQ(manager.GetCount(), 30);
}

TEST(EntityRegister, DestroyEntity_Test)
{
    EntityRegister manager;

    unsigned int entityCount = 30;

    CreateEntities(manager, 30);

    ASSERT_EQ(manager.GetCount(), entityCount);

    manager.DestroyEntity(10);

    ASSERT_EQ(manager.GetCount(), entityCount - 1);

    manager.DestroyEntity(20);

    ASSERT_EQ(manager.GetCount(), entityCount - 2);
}

TEST(EntityRegister, SetSignature_Test)
{
    Signature sig1{"0000000000000000000000000000001"};
    Signature sig2{"0000000000000000000000000000010"};
    Signature sig3 = sig1 & sig2;

    EntityRegister manager;

    manager.SetSignature(0, sig1);
    manager.SetSignature(1, sig2);
    manager.SetSignature(2, sig3);
}

TEST(EntityRegister, GetSignature_Test)
{
    Signature sig1{"0000000000000000000000000000001"};
    Signature sig2{"0000000000000000000000000000010"};
    Signature sig3 = sig1 & sig2;

    EntityRegister manager;

    manager.SetSignature(0, sig1);
    manager.SetSignature(1, sig2);
    manager.SetSignature(2, sig3);

    ASSERT_EQ(manager.GetSignature(0), sig1);
    ASSERT_EQ(manager.GetSignature(1), sig2);
    ASSERT_EQ(manager.GetSignature(2), sig3);
}