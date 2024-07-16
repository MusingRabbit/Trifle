#pragma once

#include "../Core/Entity.h"

namespace tfl
{
    class VoxelBlock : public Entity
    {
        public :
        VoxelBlock();
        VoxelBlock(const VoxelBlock& rhs);
        ~VoxelBlock();

        void SetPosition(glm::vec3 position);
        glm::vec3 GetPosition();

        void Move(glm::vec3 moveVector);
        void Rotate(glm::vec2 rotationVector);
    };
} 