#include "../Systems/CameraSystem.h"
#include "../Entities/Camera.h"
#include "../Components/Components.h"
#include "CameraSystem.h"

namespace tfl 
{
    CameraSystem::CameraSystem(unsigned int id, const SystemContext& context) : System(id, context)
    {
    }

    CameraSystem::~CameraSystem()
    {

    }

    void CameraSystem::Init()
    {

    }

    void CameraSystem::Update()
    {
        auto entityIds = GetEntityIds();

        for (unsigned int id : entityIds)
        {
            Camera camera = GetCamera(id);

            Transform& transform = camera.GetComponent<Transform>();

            if (transform.IsDirty())
            {
                UpdateTargetPosition(camera);
                transform.ResetIsDirtyFlag();
            }
        }
    }

    void CameraSystem::Draw()
    {

    }

    void CameraSystem::UpdateTargetPosition(const Camera& camera)
    {
        Target& target = camera.GetComponent<Target>();

        if (target.targetType == TARGET_NONE)
        {
            Transform& transform = camera.GetComponent<Transform>();

            // Update target offset
            glm::vec3 vRot = transform.GetRotaion();
            glm::mat4 mtxRot = MatrixHelper::CreateRotationX(vRot.x) * MatrixHelper::CreateRotationY(vRot.y);
            //glm::quat qRot = QuatHelper::CreateFromRotationMatrix(mtxRot); // TODO : There is a known bug in this function that needs to be investigated....
            glm::vec3 offset = mtxRot * glm::vec4(0, 0, 1.0f, 0.0f); //VectorHelper::Transform(glm::vec3(0, 0, 1.0f), qRot);
            target.position = transform.GetPosition() + offset;
        }
    }

    void CameraSystem::OnEntityAdded(unsigned int entityId)
    {
    }

    void CameraSystem::OnEntityRemoved(unsigned int entityId)
    {
    }

    void CameraSystem::SetCameraPosition(unsigned int entityId, glm::vec3 position)
    {
        Camera camera = GetCamera(entityId);
        camera.SetPosition(position);
    }

    void CameraSystem::MoveCamera(unsigned int entityId, glm::vec3 moveVector)
    {
        Camera camera = GetCamera(entityId);
        camera.Move(moveVector);
    }

    void CameraSystem::RotateCamera(unsigned int entityId, glm::vec2 rotationVector)
    {
        Camera camera = GetCamera(entityId);
        camera.Rotate(rotationVector);
    }

    void CameraSystem::SetCameraTarget(unsigned int entityId, unsigned int targetId)
    {
        Camera camera = GetCamera(entityId);
        camera.SetTarget(targetId);
    }

    void CameraSystem::SetCameraTarget(unsigned int entityId, glm::vec3 position)
    {
        Camera camera = GetCamera(entityId);
        camera.SetTarget(position);
    }

    void CameraSystem::ClearCameraTarget(unsigned int entityId)
    {
        Camera camera = GetCamera(entityId);
        camera.ClearTarget();
    }

    void CameraSystem::SetCameraMovementSpeed(unsigned int entityId, float movementSpeed)
    {
        Camera camera = GetCamera(entityId);
        camera.SetMovementSpeed(movementSpeed);
    }

    Camera CameraSystem::GetCamera(unsigned int entityId)
    {
        Camera result;

        result.SetId(entityId);

        return result;
    }

    Camera CameraSystem::CreateCamera(float width, float height, float zNear, float zFar)
    {
        Camera camera;

        camera.Register();
        camera.Init(width, height, zNear, zFar);
        
        AddEntity(camera.GetId());

        return camera;
    }
}