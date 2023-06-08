#ifndef QUATHELPER_H
#define QUATHELPER_H

#include <glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include<glm/common.hpp>

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

        glm::quat result;

        result.x = num9 * num6 * num5 + num8 * num7 * num4;
        result.y = num8 * num7 * num5 - num9 * num6 * num4;
        result.z = num9 * num7 * num4 - num8 * num6 * num5;
        result.w = num9 * num7 * num5 + num8 * num6 * num4;

        return result;
    }
};



#endif // QUATHELPER_H
