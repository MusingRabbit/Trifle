#include "Entity.h"

#include "../Components/Transform.h"

namespace tfl
{

Entity::Entity()
{
}

Entity::~Entity()
{
}

Entity::Entity(unsigned int entityId)
{
    SetId(entityId);
}

Entity::Entity(const Entity& rhs)
{
    SetId(rhs.m_id);
}

void Entity::Init(std::shared_ptr<EntityManager> manager)
{
    Entity::entityManager = manager;
}

void Entity::InitialisationCheck()
{
    if (Entity::entityManager == nullptr)
    {
        throw std::runtime_error("EntityManager not set. Call Entity::Init() before using the entity class.");
    }
}

Entity Entity::Create()
{
    Entity::InitialisationCheck();
    unsigned int entityId = Entity::entityManager->CreateEntity();
    Entity result(entityId);
    result.AddComponent<Transform>();
    return result;
}

void Entity::Destroy(unsigned int entityId)
{
    Entity::InitialisationCheck();
    Entity::entityManager->DestroyEntity(entityId);
}

void Entity::Register()
{
    SetId(Entity::entityManager->CreateEntity());
}

unsigned int Entity::GetId() const
{
    return m_id;
}

void Entity::SetId(unsigned int entityId)
{
    m_id = entityId;
}

void Entity::Destroy()
{
    Entity::InitialisationCheck();
    Entity::entityManager->DestroyEntity(m_id);
}

bool Entity::IsEnabled()
{
    return GetComponent<EntityData>().isEnabled;
}

void Entity::SetIsEnabled(bool value)
{
    GetComponent<EntityData>().isEnabled = value;
}

} // namespace tfl