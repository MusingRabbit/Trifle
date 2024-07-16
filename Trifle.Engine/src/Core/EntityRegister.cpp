#include "EntityRegister.h"
#include "Types.h"

namespace tfl
{
EntityRegister::EntityRegister()
{
    m_availableEntityIds = {};
    m_signatures = {};
    m_liveEntityIdCount = 0;

    for (unsigned int i = 0; i < MAX_ENTITIES; i++)
    {
        m_availableEntityIds.push(i);
    }
}

EntityRegister::~EntityRegister()
{
}

unsigned int EntityRegister::CreateEntity()
{
    assert(m_liveEntityIdCount < MAX_ENTITIES && "Too many entities in existence.");

    unsigned int result = m_availableEntityIds.front();

    m_availableEntityIds.pop();

    m_liveEntityIdCount++;

    return result;
}

void EntityRegister::DestroyEntity(unsigned int entityId)
{
    assert(entityId < MAX_ENTITIES && "Entity Id out of range.");

    m_signatures[entityId].reset();
    m_availableEntityIds.push(entityId);
    m_liveEntityIdCount--;
}

void EntityRegister::SetSignature(unsigned int entityId, Signature signature)
{
    assert(entityId < MAX_ENTITIES && "Entity Id out of range.");

    m_signatures[entityId] = signature;
}

Signature EntityRegister::GetSignature(unsigned int entityId)
{
    assert(entityId < MAX_ENTITIES && "Entity Id out of range.");

    return m_signatures[entityId];
}

unsigned int EntityRegister::GetCount()
{
    return m_liveEntityIdCount;
}
} // namespace tfl