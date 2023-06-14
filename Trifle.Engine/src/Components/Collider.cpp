#include "Collider.h"

namespace trifle
{

Collider::Collider()
{
}

Collider::Collider(const Collider& rhs)
{
    m_max = rhs.m_max;
    m_centre = rhs.m_centre; /*  */
    m_min = rhs.m_min;
    m_isTrigger = rhs.m_isTrigger;
    m_size = rhs.m_size;
}

Collider::~Collider()
{
    SetScale(1.0f);
}

bool Collider::IsEqual(const Collider& rhs)
{
    bool result = true;

    result = result && m_max == rhs.m_max;
    result = result && m_centre == rhs.m_centre;
    result = result && m_min == rhs.m_min;
    result = result && m_isTrigger == rhs.m_isTrigger;
    result = result && m_size == rhs.m_size;

    return result;
}

void Collider::SetRecalculate(bool value)
{
    m_recalculate = value;
}

bool Collider::GetRecalculate()
{
    return m_recalculate;
}

void Collider::SetIsTrigger(bool value)
{
    m_isTrigger = value;
}

bool Collider::GetIsTrigger()
{
    return m_isTrigger;
}

void Collider::SetMaximum(const glm::vec3& value)
{
    m_max.x = value.x;
    m_max.y = value.y;
    m_max.z = value.z;

    if (m_recalculate)
    {
        CalculateSize();
        CalculateCentre();
    }
}

glm::vec3 Collider::GetMaximum()
{
    return m_max;
}

void Collider::SetMinimum(const glm::vec3& value)
{
    m_min.x = value.x;
    m_min.y = value.y;
    m_min.z = value.z;

    if (m_recalculate)
    {
        CalculateSize();
        CalculateCentre();
    }
}

glm::vec3 Collider::GetMinimum()
{
    return m_min;
}

void Collider::SetCentre(float x, float y, float z)
{
    m_centre.x = x;
    m_centre.y = y;
    m_centre.z = z;
}

void Collider::SetCentre(const glm::vec3& value)
{
    SetCentre(value.x, value.y, value.z);
}

glm::vec3 Collider::GetCentre()
{
    return m_centre;
}

void Collider::SetScale(float value)
{
    SetScale(glm::vec3(value, value, value));
}

void Collider::SetScale(const glm::vec3 value)
{
    m_max.x = m_centre.x + (value.x / 2);
    m_max.y = m_centre.y + (value.y / 2);
    m_max.z = m_centre.z + (value.z / 2);

    m_min.x = m_centre.x - (value.x / 2);
    m_min.y = m_centre.y - (value.y / 2);
    m_min.z = m_centre.z - (value.z / 2);

    CalculateSize();
}

void Collider::CalculateSize()
{
    m_size = m_max - m_min;
}

void Collider::CalculateCentre()
{
    m_centre = m_max - glm::vec3(m_size.x / 2, m_size.y / 2, m_size.z / 2);
}

bool Collider::Collides(const Collider& rhs)
{
    if (m_max.x >= rhs.m_min.x &&
        m_min.x <= rhs.m_max.x) // Check that our X axis falls within the max & min of the rhs collider.
    {
        if (m_max.y < rhs.m_min.y ||
            m_min.y > rhs.m_max.y) // Check that our Y axis falls within the max & min of the rhs collider.
        {
            return false;
        }
        else
        {
            return m_max.z >= rhs.m_min.z &&
                   m_min.z <= rhs.m_max.z; // Check that our Z axis falls within the max & min of the rhs collider.
        }
    }

    return false;
}
} // namespace trifle