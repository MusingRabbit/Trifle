#include "EntityManager.h"
#include "Types.h"

EntityManager::EntityManager()
{
    for (unsigned int i = 0; i < MAX_ENTITIES; i++)
    {
        m_availableEntityIds.push(i);
    }
}

EntityManager::~EntityManager()
{
}

unsigned int EntityManager::CreateEntity()
{
    assert(m_liveEntityIdCount < MAX_ENTITIES && "Too many entities in existence.");

    unsigned int result = m_availableEntityIds.front();

    m_availableEntityIds.pop();

    m_liveEntityIdCount++;

    return result;
}

void EntityManager::DestroyEntity(unsigned int entityId)
{   
    assert(entityId < MAX_ENTITIES && "Entity Id out of range.");

    m_signatures[entityId].reset();
    m_availableEntityIds.push(entityId);
    m_liveEntityIdCount--;
}

void EntityManager::SetSignature(unsigned int entityId, Signature signature)
{
    assert(entityId < MAX_ENTITIES && "Entity Id out of range.");

    m_signatures[entityId] = signature;
}

Signature EntityManager::GetSignature(unsigned int entityId)
{
	assert(entityId < MAX_ENTITIES && "Entity Id out of range.");

    return m_signatures[entityId];
}
