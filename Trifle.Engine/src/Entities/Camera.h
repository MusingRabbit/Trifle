#ifndef CAMERA_H
#define CAMERA_H

#include "../Core/Entity.h"

namespace tfl
{
class Camera : public Entity
{
  private:
    void UpdateTargetPosition();
    //void OnTransformChangedCallback(EventArgs& e);

  public:
    Camera();
    Camera(Camera& rhs);
    ~Camera();

    void Init(float width, float height, float nearPlane, float farPlane);

    void SetPosition(glm::vec3 position);
    void Move(glm::vec3 moveVector);
    void Rotate(glm::vec2 rotationVector);
    void SetTarget(unsigned int entityId);
    void SetTarget(glm::vec3 position);
    void ClearTarget();
    void SetMovementSpeed(float value);

    float GetNearPlane();
    float GetFarPlane();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
};
} // namespace tfl

#endif // !CAMERA_H
