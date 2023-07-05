#ifndef ENTITYREGISTER_H
#define ENTITYREGISTER_H

#include "Types.h"
#include <array>
#include <cassert>
#include <queue>

#include "IEntityRegister.h"

namespace trifle
{

class EntityRegister : public IEntityRegister
{
  private:
    std::queue<unsigned int> m_availableEntityIds;
    std::array<Signature, MAX_ENTITIES> m_signatures;
    unsigned int m_liveEntityIdCount;

  public:
    EntityRegister();

    ~EntityRegister();

    unsigned int CreateEntity();
    void DestroyEntity(unsigned int entityId);
    void SetSignature(unsigned int entityId, Signature signature);
    Signature GetSignature(unsigned int entityId);

    unsigned int GetCount();
};

} // namespace trifle

#endif // !ENTITYREGISTER_H