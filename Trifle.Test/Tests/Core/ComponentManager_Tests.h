#pragma once

#include <cstdlib>
#include <glm/glm.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include <trifle.h>

using namespace tfl;

TEST(ComponentRegister, RegisterComponent_Test)
{
    ComponentRegister cmpRegister;

    cmpRegister.RegisterComponent<Transform>();
    cmpRegister.RegisterComponent<Collider>();

    unsigned int cmpsRegistered = 0;
    std::string components[2] = {"tfl::Transform", "tfl::Collider"};
    std::vector<std::string> comps = cmpRegister.GetRegisteredComponents();

    for (unsigned int i = 0; i < comps.size(); i++)
    {
        for (unsigned int j = 0; j < 2; j++)
        {
            if (comps[i] == components[j])
            {
                cmpsRegistered++;
            }
        }
    }

    ASSERT_EQ(cmpsRegistered, (unsigned int)2);
}

TEST(ComponentRegister, GetComponentType_test)
{
    ComponentRegister cmpRegister;

    cmpRegister.RegisterComponent<Transform>();
    cmpRegister.RegisterComponent<Collider>();

    unsigned int expectedTransformId = 0;
    unsigned int expectedColliderId = 1;

    unsigned int actualTransformId = cmpRegister.GetComponentType<Transform>();
    unsigned int actualColliderId = cmpRegister.GetComponentType<Collider>();

    ASSERT_EQ(expectedTransformId, actualTransformId);
    ASSERT_EQ(expectedColliderId, actualColliderId);
}

TEST(ComponentRegister, AddComponent_GetComponent_Test)
{
    ComponentRegister cmpRegister;

    unsigned int entityId1 = 0;
    unsigned int entityId2 = 1;

    cmpRegister.RegisterComponent<Transform>();
    cmpRegister.RegisterComponent<Collider>();

    Transform transform1;
    transform1.SetPosition(glm::vec3(111, 111, 111));
    transform1.Rotate(glm::vec3(111, 111, 111));
    transform1.Scale(1);

    Transform transform2;
    transform2.SetPosition(glm::vec3(222, 222, 222));
    transform2.Rotate(glm::vec3(222, 222, 222));
    transform2.Scale(2);

    Collider collider1;
    collider1.SetMaximum(glm::vec3(6, 6, 6));
    collider1.SetMinimum(glm::vec3(5, 5, 5));

    Collider collider2;
    collider2.SetMaximum(glm::vec3(3, 3, 3));
    collider2.SetMinimum(glm::vec3(2, 2, 2));

    cmpRegister.AddComponent<Transform>(entityId1, transform1);
    cmpRegister.AddComponent<Collider>(entityId1, collider1);
    cmpRegister.AddComponent<Transform>(entityId2, transform2);
    cmpRegister.AddComponent<Collider>(entityId2, collider2);

    Transform result1 = cmpRegister.GetComponent<Transform>(entityId1);
    Transform result2 = cmpRegister.GetComponent<Transform>(entityId2);

    Collider result3 = cmpRegister.GetComponent<Collider>(entityId1);
    Collider result4 = cmpRegister.GetComponent<Collider>(entityId2);

    ASSERT_EQ(cmpRegister.GetCount(), 4);
    ASSERT_TRUE(result1.IsEqual(transform1));
    ASSERT_TRUE(result2.IsEqual(transform2));
    ASSERT_TRUE(result3.IsEqual(collider1));
    ASSERT_TRUE(result4.IsEqual(collider2));
}

TEST(ComponentRegister, AddComponent_Duplicate_Test)
{
    unsigned int entityId = 100;
    ComponentRegister cmpRegister;

    cmpRegister.RegisterComponent<Transform>();

    Transform transform1;
    transform1.SetPosition(glm::vec3(111, 111, 111));
    transform1.Rotate(glm::vec3(111, 111, 111));
    transform1.Scale(1);

    Transform transform2;
    transform2.SetPosition(glm::vec3(222, 222, 222));
    transform2.Rotate(glm::vec3(222, 222, 222));
    transform2.Scale(2);

    cmpRegister.AddComponent<Transform>(entityId, transform1);

    ASSERT_DEATH(cmpRegister.AddComponent<Transform>(entityId, transform2),
                 "Duplicate addition of existing component. A component of the same type has already been mapped to this entity.");
}

TEST(ComponentRegister, RemoveComponent_Test)
{
    ComponentRegister cmpRegister;

    unsigned int entityId1 = 0;
    unsigned int entityId2 = 1;

    cmpRegister.RegisterComponent<Transform>();
    cmpRegister.RegisterComponent<Collider>();

    Transform transform1;
    transform1.SetPosition(glm::vec3(111, 111, 111));
    transform1.Rotate(glm::vec3(111, 111, 111));
    transform1.Scale(1);

    Transform transform2;
    transform2.SetPosition(glm::vec3(222, 222, 222));
    transform2.Rotate(glm::vec3(222, 222, 222));
    transform2.Scale(2);

    Collider collider1;
    collider1.SetMaximum(glm::vec3(6, 6, 6));
    collider1.SetMinimum(glm::vec3(5, 5, 5));

    Collider collider2;
    collider2.SetMaximum(glm::vec3(3, 3, 3));
    collider2.SetMinimum(glm::vec3(2, 2, 2));

    cmpRegister.AddComponent<Transform>(entityId1, transform1);
    cmpRegister.AddComponent<Collider>(entityId1, collider1);
    cmpRegister.AddComponent<Transform>(entityId2, transform2);
    cmpRegister.AddComponent<Collider>(entityId2, collider2);

    ASSERT_EQ(cmpRegister.GetCount(), 4);

    cmpRegister.RemoveComponent<Transform>(entityId1);

    ASSERT_EQ(cmpRegister.GetCount(), 3);
    ASSERT_DEATH(cmpRegister.GetComponent<Transform>(entityId1), "Retrieving non-existent component.");

    cmpRegister.RemoveComponent<Collider>(entityId2);

    ASSERT_EQ(cmpRegister.GetCount(), 2);
    ASSERT_DEATH(cmpRegister.GetComponent<Collider>(entityId2), "Retrieving non-existent component.");
}

TEST(ComponentRegister, GetComponent_Test)
{
    ComponentRegister cmpRegister;

    cmpRegister.RegisterComponent<Transform>();
    cmpRegister.RegisterComponent<Collider>();

    unsigned int entityId = 9999;

    Transform transform1;
    transform1.SetPosition(glm::vec3(111, 111, 111));
    transform1.Rotate(glm::vec3(111, 111, 111));
    transform1.Scale(1);

    Collider collider1;
    collider1.SetMaximum(glm::vec3(6, 6, 6));
    collider1.SetMinimum(glm::vec3(5, 5, 5));

    cmpRegister.AddComponent<Transform>(entityId, transform1);
    cmpRegister.AddComponent<Collider>(entityId, collider1);
    cmpRegister.AddComponent<Collider>(123, collider1);

    ASSERT_EQ(cmpRegister.GetCount(), 3);

    cmpRegister.EntityDestroyed(entityId);

    ASSERT_EQ(cmpRegister.GetCount(), 1);
}

TEST(ComponentRegister, GetCount_Test)
{
    ComponentRegister cmpRegister;

    cmpRegister.RegisterComponent<Transform>();
    cmpRegister.RegisterComponent<Collider>();

    unsigned int entityCount = rand() % 100;

    for (unsigned int i = 0; i < entityCount; i++)
    {
        Transform transform;
        transform.SetPosition(glm::vec3(std::rand(), std::rand(), std::rand()));

        Collider collider;
        collider.SetCentre(glm::vec3(std::rand(), std::rand(), std::rand()));
        collider.SetScale(1.0);

        cmpRegister.AddComponent<Transform>(i, transform);
        cmpRegister.AddComponent<Collider>(i, collider);
    }

    unsigned int componentCount = cmpRegister.GetCount();

    ASSERT_EQ(componentCount, entityCount * 2);
}