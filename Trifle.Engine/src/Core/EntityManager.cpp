#include "EntityManager.h"

#include "Components/Components.h"
#include "Systems/Systems.h"

#include <memory>

namespace trifle
{
EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::Init()
{
    m_componentRegister = std::make_unique<ComponentRegister>();
    m_entityRegister = std::make_unique<EntityRegister>();
    m_systemRegister = std::make_unique<SystemRegister>();

    RegisterComponent<EntityData>();
}

unsigned int EntityManager::CreateEntity()
{
    unsigned int entityId = m_entityRegister->CreateEntity();

    m_componentRegister->AddComponent<EntityData>(entityId, EntityData{true});

    return entityId;
}

void EntityManager::DestroyEntity(unsigned int entityId)
{
    m_entityRegister->DestroyEntity(entityId);
    m_componentRegister->EntityDestroyed(entityId);
    m_systemRegister->EntityDestroyed(entityId);
}
} // namespace trifle
