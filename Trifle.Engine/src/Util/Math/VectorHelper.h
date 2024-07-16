#ifndef VECTORHELPER_H
#define VECTORHELPER_H

#include <glm/glm.hpp>

class VectorHelper
{
  private:
    /* data */
  public:
    static glm::vec4 GetScreenSpace(const glm::vec4 ndc, float width, float height, float xOffset, float yOffset)
    {
      glm::vec4 result;

      result.x = width * (ndc.x + 1) / 2 + xOffset;
      result.y = height * (ndc.y + 1) / 2 + yOffset;
      result.z = (ndc.z +1) / 2;
      result.w = ndc.w;

      return result;
    }

    static glm::vec4 GetClipSpace(const glm::vec4& viewPos, float nearPlane, float farPlane, float width, float height)
    {
        glm::vec4 result;

        float focalLength = farPlane - nearPlane;

        result.x = focalLength * viewPos.x / (width / 2);
        result.y = focalLength * viewPos.y / (height / 2);
        result.z = -nearPlane;
        result.w = viewPos.z;

        return result;
    }

    static glm::vec4 GetNormalisedDeviceCoords(const glm::vec4 clipPos)
    {
      glm::vec4 result;
    
      result.x = clipPos.x / clipPos.w;
      result.y = clipPos.y / clipPos.w;
      result.z = clipPos.z / clipPos.w;
      result.w = 1 / clipPos.w;
      
      return result;
    }



    static glm::vec3 Transform(const glm::vec3& v, const glm::mat4 m)
    {
        float x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
        float y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
        float z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];

        return glm::vec3(x, y, z);
    }

    static glm::vec3 Transform(const glm::vec3 v, const glm::quat r)
    {
        float num = 2.0f * (r.y * v.z - r.z * v.y);
        float num2 = 2.0f * (r.z * v.x - r.x * v.z);
        float num3 = 2.0f * (r.x * v.y - r.y * v.x);

        glm::vec3 result = {};

        result.x = v.x + num * r.w + (r.y * num3 - r.z * num2);
        result.y = v.y + num2 * r.w + (r.z * num - r.x * num3);
        result.z = v.z + num3 * r.w + (r.x * num2 - r.y * num);

        return result;
    }
};

#endif // !VECTORHELPER_H