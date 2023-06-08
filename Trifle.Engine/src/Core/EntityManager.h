#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <array>
#include <cassert>
#include <queue>
#include "Types.h"

class EntityManager
{
private:
    std::queue<unsigned int> m_availableEntityIds;
    std::array<Signature, MAX_ENTITIES> m_signatures;
    unsigned int m_liveEntityIdCount;
public:
    EntityManager();

    ~EntityManager();

    unsigned int CreateEntity();
    void DestroyEntity(unsigned int entityId);
    void SetSignature(unsigned int entityId, Signature signature);
    Signature GetSignature(unsigned int entityId);
};


#endif // !ENTITYMANAGER_H