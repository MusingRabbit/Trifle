#ifndef CAMERA_H
#define CAMERA_H

#include "../Core/Entity.h"

namespace trifle
{
class Camera : public Entity
{
  private:
    void UpdateTargetPosition();

  public:
    Camera();
    ~Camera();

    void Move(glm::vec3 moveVector);
    void Rotate(glm::vec2 rotationVector);
    void SetTarget(unsigned int entityId);
    void SetTarget(glm::vec3 position);
    void ClearTarget();
};
} // namespace trifle

#endif // !CAMERA_H
