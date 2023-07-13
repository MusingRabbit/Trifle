#include "Camera.h"

#include <glm/glm.hpp>
#include "../Components/Components.h"
#include "../Util/Util.h"

namespace trifle
{
Camera::Camera() : Entity()
{
}

Camera::~Camera()
{
}

void Camera::Init(float aspectRatio, float nearPlane, float farPlane)
{
    AddComponent<Transform>();
    AddComponent<Projection>(Projection(aspectRatio, nearPlane, farPlane));
    AddComponent<Movement>();
    AddComponent<Target>();

    std::function<void(EventArgs&)> func = [this](EventArgs& e) { this->OnTransformChangedCallback(e); };

    Transform& transform = GetComponent<Transform>();

    transform.OnPositionChanged.UnSubscribe();
    transform.OnRotationChanged.UnSubscribe();

    transform.OnPositionChanged.Subscribe(func);
    transform.OnRotationChanged.Subscribe(func);
}

void Camera::SetPosition(glm::vec3 position)
{
    Transform& transform = GetComponent<Transform>();
    transform.SetPosition(position);
}

void Camera::Move(glm::vec3 moveVector)
{
    Transform& transform = GetComponent<Transform>();
    glm::vec3 rot = transform.GetRotaion();

    glm::mat4 rotate = MatrixHelper::CreateRotationX(rot.x) * MatrixHelper::CreateRotationY(rot.y);

    float movementSpeed = GetComponent<Movement>().speed;
    glm::vec3 movement = movementSpeed * moveVector;
    movement = VectorHelper::Transform(movement, rotate);
    movement = transform.GetPosition() + movement;

    transform.SetPosition(movement);
}

void Camera::Rotate(glm::vec2 rotationVector)
{
    Transform& transform = GetComponent<Transform>();

    float xRot = transform.GetRotaion().x + rotationVector.x;
    float xRotMin = -(glm::pi<float>() / 2) + 0.01f;
    float xRotMax = (glm::pi<float>() / 2) - 0.01f;

    xRot = glm::clamp(xRot, xRotMin, xRotMax);
    float yRot = transform.GetRotaion().y + rotationVector.y;
    float zRot = 0.0f;

    transform.SetRotation(xRot, yRot, zRot);
}

void Camera::SetTarget(unsigned int entityId)
{
    Target& target = GetComponent<Target>();
    target.targetType = TARGET_ENTITY;
    target.entityId = entityId;
}

void Camera::SetTarget(glm::vec3 position)
{
    Target& target = GetComponent<Target>();
    target.targetType = TARGET_POSITION;
    target.position = position;
}

void Camera::ClearTarget()
{
    Target& target = GetComponent<Target>();
    target.targetType = TARGET_NONE;
    target.entityId = -1;
}

void Camera::SetMovementSpeed(float value)
{
    GetComponent<Movement>().speed = value;
}

glm::mat4 Camera::GetViewMatrix()
{
    Transform& transform = GetComponent<Transform>();
    Target& target = GetComponent<Target>();

    return glm::lookAtLH(transform.GetPosition(), target.position, glm::vec3(0, 1, 0));

    // return MatrixHelper::CreateLookAtMatrix(transform.GetPosition(), target.position, glm::vec3(0, 1, 0));
}

void Camera::OnTransformChangedCallback(EventArgs& e)
{
    UpdateTargetPosition();
}

void Camera::UpdateTargetPosition()
{
    Target& target = GetComponent<Target>();

    if (target.targetType == TARGET_NONE)
    {
        Transform& transform = GetComponent<Transform>();

        // Update target offset
        glm::vec3 vRot = transform.GetRotaion();
        glm::mat4 mtxRot = MatrixHelper::CreateRotationX(vRot.x) * MatrixHelper::CreateRotationY(vRot.y);
        glm::quat qRot = QuatHelper::CreateFromRotationMatrix(mtxRot);
        glm::vec3 offset = VectorHelper::Transform(glm::vec3(0, 0, 1), qRot);
        target.position = transform.GetPosition() + offset;
    }
}

}; // namespace trifle
