#include "Camera.h"

#include <glm/glm.hpp>
#include "../Components/Components.h"
#include "../Util/Util.h"

using namespace tfl;

Camera::Camera() : Entity()
{
}

Camera::Camera(Camera& rhs) : Entity(rhs)
{
}

Camera::~Camera()
{
}

void Camera::Init(float width, float height, float nearPlane, float farPlane)
{
    AddComponent<Transform>();
    AddComponent<Projection>(Projection(width / height, nearPlane, farPlane));
    AddComponent<Movement>();
    AddComponent<Target>();

    //std::function<void(EventArgs&)> func = [this](EventArgs& e) { this->OnTransformChangedCallback(e); };

    //Transform& transform = GetComponent<Transform>();

    //transform.InitCallbacks();

    //transform.OnPositionChanged.UnSubscribe();
    //transform.OnRotationChanged.UnSubscribe();

    //transform.OnPositionChanged.Subscribe(func);
    //transform.OnRotationChanged.Subscribe(func);
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
    glm::vec3 movement = movementSpeed * glm::normalize(moveVector);
    movement = VectorHelper::Transform(movement, rotate);
    movement = transform.GetPosition() + movement;

    transform.SetPosition(movement);
}

void Camera::Rotate(glm::vec2 rotationVector)
{
    Transform& transform = GetComponent<Transform>();
    transform.Rotate({rotationVector.x,rotationVector.y,0.0f});
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

float Camera::GetNearPlane()
{
    return GetComponent<Projection>().GetNearPlane();
}

float Camera::GetFarPlane()
{
    return GetComponent<Projection>().GetFarPlane();
}

glm::mat4 Camera::GetViewMatrix()
{
    Transform& transform = GetComponent<Transform>();
    Target& target = GetComponent<Target>();

    glm::vec3 camPos = transform.GetPosition();
    glm::vec3 tgtPos = target.position;

    return glm::lookAtLH(camPos, tgtPos, glm::vec3(0, 1, 0));

    //return MatrixHelper::CreateLookAtMatrix(transform.GetPosition(), target.position, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return GetComponent<Projection>().GetMatrix();
}

/* void Camera::OnTransformChangedCallback(EventArgs& e)
{
    UpdateTargetPosition();
}
 */

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
        glm::vec3 offset = VectorHelper::Transform(glm::vec3(0, 0, 10), qRot);
        target.position = transform.GetPosition() + offset;
    }
}