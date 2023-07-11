#ifndef CAMERA_H
#define CAMERA_H

#include "../Core/Entity.h"

namespace trifle
{
class Camera : public Entity
{
  private:
    void UpdateTargetPosition();
    void OnTransformChangedCallback(EventArgs& e);

  public:
    Camera();
    ~Camera();

    void Init(float aspectRatio, float nearPlane, float farPlane);

    void SetPosition(glm::vec3 position);
    void Move(glm::vec3 moveVector);
    void Rotate(glm::vec2 rotationVector);
    void SetTarget(unsigned int entityId);
    void SetTarget(glm::vec3 position);
    void ClearTarget();
    void SetMovementSpeed(float value);

    glm::mat4 GetViewMatrix();
};
} // namespace trifle

#endif // !CAMERA_H
