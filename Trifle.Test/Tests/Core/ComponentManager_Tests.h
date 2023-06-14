#pragma Once

#include <cstdlib>
#include <glm/glm.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include <Components/Components.h>
#include <Core/ComponentManager.h>

using namespace trifle;

TEST(ComponentManager, RegisterComponent_Test)
{
    ComponentManager cmpManager;

    cmpManager.RegisterComponent<Transform>();
    cmpManager.RegisterComponent<Collider>();

    unsigned int cmpsRegistered = 0;
    std::string components[2] = {"trifle::Transform", "trifle::Collider"};
    std::vector<std::string> comps = cmpManager.GetRegisteredComponents();

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

TEST(ComponentManager, GetComponentType_test)
{
    ComponentManager cmpManager;

    cmpManager.RegisterComponent<Transform>();
    cmpManager.RegisterComponent<Collider>();

    unsigned int expectedTransformId = 0;
    unsigned int expectedColliderId = 1;

    unsigned int actualTransformId = cmpManager.GetComponentType<Transform>();
    unsigned int actualColliderId = cmpManager.GetComponentType<Collider>();

    ASSERT_EQ(expectedTransformId, actualTransformId);
    ASSERT_EQ(expectedColliderId, actualColliderId);
}

TEST(ComponentManager, AddComponent_GetComponent_Test)
{
    ComponentManager cmpManager;

    unsigned int entityId1 = 0;
    unsigned int entityId2 = 1;

    cmpManager.RegisterComponent<Transform>();
    cmpManager.RegisterComponent<Collider>();

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

    cmpManager.AddComponent<Transform>(entityId1, transform1);
    cmpManager.AddComponent<Collider>(entityId1, collider1);
    cmpManager.AddComponent<Transform>(entityId2, transform2);
    cmpManager.AddComponent<Collider>(entityId2, collider2);

    Transform result1 = cmpManager.GetComponent<Transform>(entityId1);
    Transform result2 = cmpManager.GetComponent<Transform>(entityId2);

    Collider result3 = cmpManager.GetComponent<Collider>(entityId1);
    Collider result4 = cmpManager.GetComponent<Collider>(entityId2);

    ASSERT_EQ(cmpManager.GetCount(), 4);
    ASSERT_TRUE(result1.IsEqual(transform1));
    ASSERT_TRUE(result2.IsEqual(transform2));
    ASSERT_TRUE(result3.IsEqual(collider1));
    ASSERT_TRUE(result4.IsEqual(collider2));
}

TEST(ComponentManager, AddComponent_Duplicate_Test)
{
    unsigned int entityId = 100;
    ComponentManager cmpManager;

    cmpManager.RegisterComponent<Transform>();

    Transform transform1;
    transform1.SetPosition(glm::vec3(111, 111, 111));
    transform1.Rotate(glm::vec3(111, 111, 111));
    transform1.Scale(1);

    Transform transform2;
    transform2.SetPosition(glm::vec3(222, 222, 222));
    transform2.Rotate(glm::vec3(222, 222, 222));
    transform2.Scale(2);

    cmpManager.AddComponent<Transform>(entityId, transform1);

    ASSERT_DEATH(
        cmpManager.AddComponent<Transform>(entityId, transform2),
        "Duplicate addition of existing component. A component of the same type has already been mapped to this entity.");
}

TEST(ComponentManager, RemoveComponent_Test)
{
    ComponentManager cmpManager;

    unsigned int entityId1 = 0;
    unsigned int entityId2 = 1;

    cmpManager.RegisterComponent<Transform>();
    cmpManager.RegisterComponent<Collider>();

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

    cmpManager.AddComponent<Transform>(entityId1, transform1);
    cmpManager.AddComponent<Collider>(entityId1, collider1);
    cmpManager.AddComponent<Transform>(entityId2, transform2);
    cmpManager.AddComponent<Collider>(entityId2, collider2);

    ASSERT_EQ(cmpManager.GetCount(), 4);

    cmpManager.RemoveComponent<Transform>(entityId1);

    ASSERT_EQ(cmpManager.GetCount(), 3);
    ASSERT_DEATH(cmpManager.GetComponent<Transform>(entityId1), "Retrieving non-existent component.");

    cmpManager.RemoveComponent<Collider>(entityId2);

    ASSERT_EQ(cmpManager.GetCount(), 2);
    ASSERT_DEATH(cmpManager.GetComponent<Collider>(entityId2), "Retrieving non-existent component.");
}

TEST(ComponentManager, GetComponent_Test)
{
    ComponentManager cmpManager;

    cmpManager.RegisterComponent<Transform>();
    cmpManager.RegisterComponent<Collider>();

    unsigned int entityId = 9999;

    Transform transform1;
    transform1.SetPosition(glm::vec3(111, 111, 111));
    transform1.Rotate(glm::vec3(111, 111, 111));
    transform1.Scale(1);

    Collider collider1;
    collider1.SetMaximum(glm::vec3(6, 6, 6));
    collider1.SetMinimum(glm::vec3(5, 5, 5));

    cmpManager.AddComponent<Transform>(entityId, transform1);
    cmpManager.AddComponent<Collider>(entityId, collider1);
    cmpManager.AddComponent<Collider>(123, collider1);

    ASSERT_EQ(cmpManager.GetCount(), 3);

    cmpManager.EntityDestroyed(entityId);

    ASSERT_EQ(cmpManager.GetCount(), 1);
}

TEST(ComponentManager, GetCount_Test)
{
    ComponentManager cmpManager;

    cmpManager.RegisterComponent<Transform>();
    cmpManager.RegisterComponent<Collider>();

    unsigned int entityCount = rand() % 100;

    for (unsigned int i = 0; i < entityCount; i++)
    {
        Transform transform;
        transform.SetPosition(glm::vec3(std::rand(), std::rand(), std::rand()));

        Collider collider;
        collider.SetCentre(glm::vec3(std::rand(), std::rand(), std::rand()));
        collider.SetScale(1.0);

        cmpManager.AddComponent<Transform>(i, transform);
        cmpManager.AddComponent<Collider>(i, collider);
    }

    unsigned int componentCount = cmpManager.GetCount();

    ASSERT_EQ(componentCount, entityCount * 2);
}