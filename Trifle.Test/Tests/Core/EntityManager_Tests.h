#pragma Once

#include <gtest/gtest.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <Core/EntityManager.h>

using namespace trifle;

void CreateEntities(EntityManager& manager, unsigned int entityCount)
{
    for (unsigned int i = 0; i < entityCount; i++)
    {
        manager.CreateEntity();
    }
}

TEST(EntityManager, CreateEntity_Test)
{
    EntityManager manager;
    CreateEntities(manager, 30);

    ASSERT_EQ(manager.GetCount(), 30);
}

TEST(EntityManager, DestroyEntity_Test)
{
    EntityManager manager;

    unsigned int entityCount = 30;

    CreateEntities(manager, 30);

    ASSERT_EQ(manager.GetCount(), entityCount);

    manager.DestroyEntity(10);

    ASSERT_EQ(manager.GetCount(), entityCount - 1);

    manager.DestroyEntity(20);

    ASSERT_EQ(manager.GetCount(), entityCount - 2);
}

TEST(EntityManager, SetSignature_Test)
{
    Signature sig1{"0000000000000000000000000000001"};
    Signature sig2{"0000000000000000000000000000010"};
    Signature sig3 = sig1 & sig2;

    EntityManager manager;

    manager.SetSignature(0, sig1);
    manager.SetSignature(1, sig2);
    manager.SetSignature(2, sig3);
}

TEST(EntityManager, GetSignature_Test)
{
    Signature sig1{"0000000000000000000000000000001"};
    Signature sig2{"0000000000000000000000000000010"};
    Signature sig3 = sig1 & sig2;

    EntityManager manager;

    manager.SetSignature(0, sig1);
    manager.SetSignature(1, sig2);
    manager.SetSignature(2, sig3);

    ASSERT_EQ(manager.GetSignature(0), sig1);
    ASSERT_EQ(manager.GetSignature(1), sig2);
    ASSERT_EQ(manager.GetSignature(2), sig3);
}