#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "../Core/Entity.h"

#include <memory>

namespace trifle
{
class EntityBuilder
{
  private:
  public:
    static Entity MakeCamera(float aspectRatio, float nearPlane, float farPlane);
    static Entity CreateTexturedQuad();
};
} // namespace trifle

#endif // !GAMEOBJECTFACTORY_H
