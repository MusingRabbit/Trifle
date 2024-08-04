#pragma once

#include <glm/glm.hpp>

namespace tfl
{
struct BoundingBox
{
    glm::vec3 min;
    glm::vec3 max;

    BoundingBox()
    {
        min = {};
        max = {};
    }

    BoundingBox(const glm::vec3& minV, const glm::vec3& maxV)
    {
        min.x = minV.x;
        min.y = minV.y;
        min.z = minV.z;

        max.x = maxV.x;
        max.y = maxV.y;
        max.z = maxV.z;
    }

    BoundingBox(const BoundingBox& rhs)
    {
        min = rhs.min;
        max = rhs.max;
    }

    glm::vec3 GetCentre() const
    {
        glm::vec3 total = (min + max);
        return {total.x / 2, total.y / 2, total.z / 2};
    }

    ~BoundingBox()
    {

    }

    //void SetMax(const glm::vec3& max)
    //{
    //    max.x = max.x;
    //    max.y = max.y;
    //    max.z = max.z;
    //}
//
    //void SetMin(const glm::vec3& min)
    //{
    //    min.x = min.x;
    //    min.y = min.y;
    //    min.z = min.z;
    //}

    bool Contains(const BoundingBox& rhs)
    {
        return (Contains(rhs.min) && Contains(rhs.max));
    }

    bool Contains(const glm::vec3 point)
    {
        bool lessThanMax = max.x > point.x && max.y > point.y && max.z > point.z;
        bool greaterthanMin = min.x < point.x && min.y < point.y && min.z < point.z;
        return lessThanMax && greaterthanMin;
    }
};
}

