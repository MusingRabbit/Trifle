#ifndef QUATHELPER_H
#define QUATHELPER_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>

namespace trifle
{
class QuatHelper
{
  private:
  public:
    static glm::quat CreateFromYawPitchRoll(float yaw, float pitch, float roll)
    {
        float num = roll * 0.5f;
        float num2 = pitch * 0.5f;
        float num3 = yaw * 0.5f;
        float num4 = glm::sin(num);
        float num5 = glm::cos(num);
        float num6 = glm::sin(num2);
        float num7 = glm::cos(num2);
        float num8 = glm::sin(num3);
        float num9 = glm::cos(num3);

        glm::quat result = {};

        result.x = num9 * num6 * num5 + num8 * num7 * num4;
        result.y = num8 * num7 * num5 - num9 * num6 * num4;
        result.z = num9 * num7 * num4 - num8 * num6 * num5;
        result.w = num9 * num7 * num5 + num8 * num6 * num4;

        return result;
    }

    static glm::quat CreateFromRotationMatrix(const glm::mat4& m)
    {
        glm::quat result = {};
        float num = m[0][0] + m[1][1] + m[2][2];

        float num2, num3;

        if (num > 0.0f)
        {
            num2 = sqrt(num + 1.0f);
            num3 = 0.5f / num2;
            result.x = (m[1][2] - m[2][1]) * num3;
            result.y = (m[2][0] - m[0][2]) * num3;
            result.z = (m[0][1] - m[1][0]) * num3;
            result.w = num2 * 0.5f;
            return result;
        }

        if (m[0][0] >= m[1][1] && m[0][0] >= m[2][2])
        {
            num2 = sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]);
            num3 = 0.5f / num2;
            result.x = 0.5f * num2;
            result.y = (m[0][1] + m[1][0]) * num3;
            result.z = (m[0][2] + m[2][0]) * num3;
            result.w = (m[1][2] + m[2][1]) * num3;
        }

        if (m[1][1] > m[2][2])
        {
            num2 = sqrt(1.0f + m[1][1] - m[0][0] - m[2][2]);
            num3 = 0.5f / num2;
            result.x = (m[1][0] + m[0][1]) * num3;
            result.y = 0.5 * num2;
            result.z = (m[2][1] + m[1][2]) * num3;
            result.w = (m[2][0] + m[0][2]) * num3;
            return result;
        }

        num2 = sqrt(1.0f + m[2][2] - m[0][0] - m[1][1]);
        num3 = 0.5f / num2;
        result.x = (m[2][0] + m[0][2]) * num3;
        result.y = (m[2][1] + m[1][2]) * num3;
        result.z = 0.5f * num2;
        result.w = (m[0][1] - m[1][0]) * num3;

        return result;
    }
};
} // namespace trifle

#endif // QUATHELPER_H
