#pragma once

#include <glm/glm.hpp>

namespace tfl
{
struct BoundingBox
{
    glm::vec3 m_min;
    glm::vec3 m_max;

    BoundingBox()
    {
        m_min = {};
        m_max = {};
    }

    BoundingBox(const glm::vec3& min, const glm::vec3& max)
    {
        m_min.x = min.x;
        m_min.y = min.y;
        m_min.z = min.z;

        m_max.x = max.x;
        m_max.y = max.y;
        m_max.z = max.z;
    }

    BoundingBox(const BoundingBox& rhs)
    {
        m_min = rhs.m_min;
        m_max = rhs.m_max;
    }

    ~BoundingBox()
    {

    }

    void SetMax(const glm::vec3& max)
    {
        m_max.x = max.x;
        m_max.y = max.y;
        m_max.z = max.z;
    }

    void SetMin(const glm::vec3& min)
    {
        m_min.x = min.x;
        m_min.y = min.y;
        m_min.z = min.z;
    }

    bool Contains(const glm::vec3 point)
    {
        bool lessThanMax = m_max.x > point.x && m_max.y > point.y && m_max.z > point.z;
        bool greaterthanMin = m_min.x < point.x && m_min.y < point.y && m_min.z < point.z;
        return lessThanMax && greaterthanMin;
    }
};
}

