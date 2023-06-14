#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Types.h"
#include <array>
#include <cassert>
#include <queue>

namespace trifle
{

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

    unsigned int GetCount();
};

} // namespace trifle

#endif // !ENTITYMANAGER_H