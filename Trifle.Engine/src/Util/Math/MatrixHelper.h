#ifndef MATRIXHELPER_H
#define MATRIXHELPER_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>

#include "QuatHelper.h"

namespace tfl
{
class MatrixHelper
{
  public:
    static glm::mat4 CreateTranslationMatrix(glm::vec3 vector)
    {
        glm::mat4 result = glm::identity<glm::mat4>();
        result[3][0] = vector.x;
        result[3][1] = vector.y;
        result[3][2] = vector.z;
        return result;
    }

    static glm::mat4 CreateScaleMatrix(glm::vec3 vector)
    {
        glm::mat4 result = glm::identity<glm::mat4>();
        result[0][0] = vector.x;
        result[1][1] = vector.y;
        result[2][2] = vector.z;
        return result;
    }

    static glm::mat4 CreateRotationMatrix(glm::vec3 vector)
    {
        glm::quat qRot = QuatHelper::CreateFromYawPitchRoll(vector.x, vector.y, vector.z);
        return GetMatrixFromQuat(qRot);
    }

    static glm::mat4 GetMatrixFromQuat(glm::quat q)
    {
        float num   = q.x * q.x;
        float num2  = q.y * q.y;
        float num3  = q.z * q.z;
        float num4  = q.x * q.y;
        float num5  = q.z * q.w;
        float num6  = q.z * q.x;
        float num7  = q.y * q.w;
        float num8  = q.y * q.z;
        float num9  = q.x * q.w;

        glm::mat4 result;

        result[0][0]    = 1.0f - 2.0f * (num2 + num3);
        result[0][1]    = 2.0f * (num4 + num5);
        result[0][2]    = 2.0f * (num6 - num7);
        result[0][3]    = 0.0f;
        result[1][0]    = 2.0f * (num4 - num5);
        result[1][1]    = 1.0f - 2.0f * (num3 + num);
        result[1][2]    = 2.0f * (num8 + num9);
        result[1][3]    = 0.0f;
        result[2][0]    = 2.0f * (num6 + num7);
        result[2][1]    = 2.0f * (num8 - num9);
        result[2][2]    = 1.0f - 2.0f * (num2 + num);
        result[2][3]    = 0.0f;
        result[3][0]    = 0.0f;
        result[3][1]    = 0.0f;
        result[3][2]    = 0.0f;
        result[3][3]    = 1.0f;
        
        return result;   
    }

    static glm::mat4 CreateProjectionMatrix(float width, float height, float nearPlane, float farPlane)
    {
        glm::mat4 result = {};

        float q = farPlane / (farPlane - nearPlane);

        result[0][0] = 2.0f * nearPlane / width;
        result[1][1] = 2.0f * nearPlane / height;
        result[2][2] = q;
        result[2][3] = -1.0f;
        result[3][2] = nearPlane * q;

        return result;
    }

    static glm::mat4 CreateLookAtMatrix(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up)
    {
        glm::mat4 result = {};

        glm::vec3 v1 = glm::normalize(pos - target);
        glm::vec3 v2 = glm::normalize(glm::cross(up, v1));
        glm::vec3 v3 = glm::cross(v1, v2);

        float dotV1 = glm::dot(v1, pos);
        float dotV2 = glm::dot(v2, pos);
        float dotV3 = glm::dot(v3, pos);

        result[0][0] = v2.x;
        result[0][1] = v3.x;
        result[0][2] = v1.x;
        result[0][3] = 0.0f;

        result[1][0] = v2.y;
        result[1][1] = v3.y;
        result[1][2] = v1.y;
        result[1][3] = 0.0f;

        result[2][0] = v2.z;
        result[2][1] = v3.z;
        result[2][2] = v1.z;
        result[2][3] = 0.0f;

        result[3][0] = 0.0f - dotV2;
        result[3][1] = 0.0f - dotV3;
        result[3][2] = 0.0f - dotV1;
        result[3][3] = 1.0f;

        return result;
    }

    static glm::mat4 CreateRotationX(float radians)
    {
        glm::mat4 result = glm::identity<glm::mat4>();

        float cosR = cos(radians);
        float sinR = sin(radians);

        result[1][1] = cosR;
        result[1][2] = sinR;
        result[2][1] = 0.0f - sinR;
        result[2][2] = cosR;

        return result;
    }

    static glm::mat4 CreateRotationY(float radians)
    {
        glm::mat4 result = glm::identity<glm::mat4>();

        float cosR = cos(radians);
        float sinR = sin(radians);

        result[0][0] = cosR;
        result[0][2] = 0.0f - sinR;
        result[2][0] = sinR;
        result[2][2] = cosR;

        return result;
    }

    static glm::mat4 CreateRotationZ(float radians)
    {
        glm::mat4 result = glm::identity<glm::mat4>();

        float cosR = cos(radians);
        float sinR = sin(radians);

        result[0][0] = cosR;
        result[0][1] = sinR;
        result[1][0] = 0.0f - sinR;
        result[1][1] = cosR;

        return result;
    }
};
} // namespace tfl
#endif // !MATRIXHELPER_H
