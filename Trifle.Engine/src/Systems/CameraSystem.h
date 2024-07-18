#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "../Entities/Camera.h"
#include "../Core/System.h"

namespace tfl
{
    class CameraSystem : public System
    {
        private :
        void UpdateTargetPosition(const Camera& camera);

        protected :
        void OnEntityAdded(unsigned int entityId) override;
        void OnEntityRemoved(unsigned int entityId) override;

        public :
        CameraSystem(unsigned int id, const SystemContext& context);
        ~CameraSystem();

        void Init() override;
        void Update() override;
        void Draw() override;

        void SetCameraPosition(unsigned int entityId, glm::vec3 position);
        void MoveCamera(unsigned int entityId, glm::vec3 moveVector);
        void RotateCamera(unsigned int entityId, glm::vec2 rotationVector);
        void SetCameraTarget(unsigned int entityId, unsigned int targetId);
        void SetCameraTarget(unsigned int entityid, glm::vec3 position);
        void ClearCameraTarget(unsigned int entityId);
        void SetCameraMovementSpeed(unsigned int entityId, float movementSpeed);

        Camera GetCamera(unsigned int entityId);
        Camera CreateCamera(float with, float height, float zNear, float zFar);
    };
}
#endif