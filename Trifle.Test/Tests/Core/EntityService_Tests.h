#pragma Once

#include <gtest/gtest.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <Core/Core.h>
#include <Systems/Systems.h>

using namespace trifle;

void InitialiseService(EntityService& service, unsigned int entityCount)
{
    service.Init();

    for (unsigned int i = 0; i < entityCount; i++)
    {
        service.CreateEntity();
    }
}

TEST(EntityService, CreateEntity_Test)
{
    EntityService service;
    service.Init();

    unsigned int iEntity0 = service.CreateEntity();
    unsigned int iEntity1 = service.CreateEntity();
    unsigned int iEntity2 = service.CreateEntity();

    ASSERT_EQ(iEntity0, 0);
    ASSERT_EQ(iEntity1, 1);
    ASSERT_EQ(iEntity2, 2);
}

TEST(EntityService, DestroyEntity_Test)
{
    EntityService service;
    InitialiseService(service, 30);

    service.DestroyEntity(10);
}

TEST(EntityService, RegisterComponent_Test)
{
    EntityService service;
    InitialiseService(service, 30);

    service.RegisterComponent<Transform>();
    service.RegisterComponent<Collider>();
}

TEST(EntityService, AddComponent_GetComponent_Test)
{
    EntityService service;
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

TEST(EntityService, RemoveComponent_Test)
{
    EntityService service;
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

TEST(EntityService, RegisterEntityOnSystem_Test)
{
    EntityService service;
    InitialiseService(service, 30);

    service.RegisterSystem<VoxelRenderSystem>();

    for (unsigned int i = 0; i < 30; i++)
    {
        service.RegisterEntityOnSystem<VoxelRenderSystem>(i);
    }
}

TEST(EntityService, GetSystem_Test)
{
    EntityService service;
    InitialiseService(service, 30);

    service.RegisterSystem<VoxelRenderSystem>();

    std::shared_ptr<VoxelRenderSystem> system = service.GetSystem<VoxelRenderSystem>();

    for (unsigned int i = 0; i < 30; i++)
    {
        service.RegisterEntityOnSystem<VoxelRenderSystem>(i);
    }

    ASSERT_EQ(system->GetEntityCount(), 30);
}

TEST(EntityService, RemoveEntityOnSystem_Test)
{
    EntityService service;
    InitialiseService(service, 30);

    service.RegisterSystem<VoxelRenderSystem>();

    std::shared_ptr<VoxelRenderSystem> system = service.GetSystem<VoxelRenderSystem>();

    for (unsigned int i = 0; i < 30; i++)
    {
        service.RegisterEntityOnSystem<VoxelRenderSystem>(i);
    }

    for (unsigned int i = 0; i < 15; i++)
    {
        service.RemoveEntityOnSystem<VoxelRenderSystem>(i);
    }

    ASSERT_EQ(system->GetEntityCount(), 15);
}

TEST(EntityService, GetComponentType_Test)
{
    EntityService service;
    InitialiseService(service, 0);

    service.RegisterComponent<Transform>();
    service.RegisterComponent<Collider>();

    ASSERT_EQ(service.GetComponentType<Transform>(), 0);
    ASSERT_EQ(service.GetComponentType<Collider>(), 1);
}