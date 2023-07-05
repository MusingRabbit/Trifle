#ifndef IENTITYREGISTER_H
#define IENTITYREGISTER_H

#include "Types.h"

namespace trifle
{
class IEntityRegister
{
    virtual unsigned int CreateEntity() = 0;
    virtual void DestroyEntity(unsigned int entityId) = 0;
    virtual void SetSignature(unsigned int entityId, Signature signature) = 0;
    virtual Signature GetSignature(unsigned int entityId) = 0;
    virtual unsigned int GetCount() = 0;
};
} // namespace trifle

#endif