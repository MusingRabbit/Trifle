#pragma Once

#include <gtest/gtest.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <Core/Core.h>
#include <Systems/Systems.h>

using namespace trifle;

void InitialiseService(EntityManager& service, unsigned int entityCount)
{
    service.Init();

    for (unsigned int i = 0; i < entityCount; i++)
    {
        service.CreateEntity();
    }
}

TEST(EntityManager, CreateEntity_Test)
{
    EntityManager service;
    service.Init();

    unsigned int iEntity0 = service.CreateEntity();
    unsigned int iEntity1 = service.CreateEntity();
    unsigned int iEntity2 = service.CreateEntity();

    ASSERT_EQ(iEntity0, 0);
    ASSERT_EQ(iEntity1, 1);
    ASSERT_EQ(iEntity2, 2);
}

TEST(EntityManager, DestroyEntity_Test)
{
    EntityManager service;
    InitialiseService(service, 30);

    service.DestroyEntity(10);
}

TEST(EntityManager, RegisterComponent_Test)
{
    EntityManager service;
    InitialiseService(service, 30);

    service.RegisterComponent<Transform>();
    service.RegisterComponent<Collider>();
}

TEST(EntityManager, AddComponent_GetComponent_Test)
{
    EntityManager service;
    InitialiseService(service, 30);

    service.RegisterComponent<Transform>();
    service.RegisterComponent<Collider>();

    std::vector<Transform> transforms;
    std::vector<Collider> colliders;

    for (unsigned int i = 0; i < 30; i++)
    {
        Transform transform;
        Collider collider;

        transform.SetPosition(std::rand(), std::rand(), std::rand());
        collider.SetCentre(std::rand(), std::rand(), std::rand());
        collider.SetScale(1.0f);

        transforms.push_back(transform);
        colliders.push_back(collider);

        service.AddComponent<Transform>(i, transform);
        service.AddComponent<Collider>(i, collider);
    }

    for (unsigned int i = 0; i < 30; i++)
    {
        Transform transform = transforms[i];
        Collider collider = colliders[i];

        bool transformMatch = transform.IsEqual(service.GetComponent<Transform>(i));
        bool colliderMatch = collider.IsEqual(service.GetComponent<Collider>(i));

        ASSERT_TRUE(transformMatch && colliderMatch);
    }
}

TEST(EntityManager, RemoveComponent_Test)
{
    EntityManager service;
    InitialiseService(service, 30);

    service.RegisterComponent<Transform>();
    service.RegisterComponent<Collider>();

    for (unsigned int i = 0; i < 30; i++)
    {
        Transform transform;
        Collider collider;

        service.AddComponent<Transform>(i, transform);
        service.AddComponent<Collider>(i, collider);
    }

    for (unsigned int i = 0; i < 30; i++)
    {
        service.RemoveComponent<Transform>(i);
    }
}

TEST(EntityManager, RegisterEntityOnSystem_Test)
{
    EntityManager service;
    InitialiseService(service, 30);

    service.RegisterSystem<Renderer>();

    for (unsigned int i = 0; i < 30; i++)
    {
        service.RegisterEntityOnSystem<Renderer>(i);
    }
}

TEST(EntityManager, GetSystem_Test)
{
    EntityManager service;
    InitialiseService(service, 30);

    service.RegisterSystem<Renderer>();

    std::shared_ptr<Renderer> system = service.GetSystem<Renderer>();

    for (unsigned int i = 0; i < 30; i++)
    {
        service.RegisterEntityOnSystem<Renderer>(i);
    }

    ASSERT_EQ(system->GetEntityCount(), 30);
}

TEST(EntityManager, RemoveEntityOnSystem_Test)
{
    EntityManager service;
    InitialiseService(service, 30);

    service.RegisterSystem<Renderer>();

    std::shared_ptr<Renderer> system = service.GetSystem<Renderer>();

    for (unsigned int i = 0; i < 30; i++)
    {
        service.RegisterEntityOnSystem<Renderer>(i);
    }

    for (unsigned int i = 0; i < 15; i++)
    {
        service.RemoveEntityOnSystem<Renderer>(i);
    }

    ASSERT_EQ(system->GetEntityCount(), 15);
}

TEST(EntityManager, GetComponentType_Test)
{
    EntityManager service;
    InitialiseService(service, 0);

    service.RegisterComponent<Transform>();
    service.RegisterComponent<Collider>();

    ComponentType transformType = service.GetComponentType<Transform>();
    ComponentType colliderType = service.GetComponentType<Collider>();

    ASSERT_EQ(transformType, 1);
    ASSERT_EQ(colliderType, 2);
}