#ifndef MATRIXHELPER_H
#define MATRIXHELPER_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>

#include "QuatHelper.h"

namespace trifle
{
    class MatrixHelper
    {
    public:
        static glm::mat4 CreateTranslationMatrix(glm::vec3 vector)
        {
            glm::mat4 result;
            result[3][0] = vector.x;
            result[3][1] = vector.y;
            result[3][2] = vector.z;
            return result;
        }

        static glm::mat4 CreateScaleMatrix(glm::vec3 vector)
        {
            glm::mat4 result;
            result[0][0] = vector.x;
            result[1][1] = vector.y;
            result[2][2] = vector.z;
            return result;
        }

        static glm::mat4 CreateRotationMatrix(glm::vec3 vector)
        {
            glm::quat qRot = QuatHelper::CreateFromYawPitchRoll(vector.x, vector.y, vector.z);
            return glm::mat4_cast(qRot);
        }
    };
}
#endif // !MATRIXHELPER_H
