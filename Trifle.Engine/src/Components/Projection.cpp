#include "Projection.h"

#include "../Util/Util.h"
#include <stdexcept>

namespace trifle
{
Projection::Projection()
{
    Init(1.0f, 1.0f, 1000.0f);
}

Projection::Projection(float aspectRatio, float nearPlane, float farPlane)
{
    Init(aspectRatio, nearPlane, farPlane);
}

Projection::~Projection()
{
}

Projection::Projection(const Projection& rhs)
{
    m_near = rhs.m_near;
    m_far = rhs.m_far;
    m_aspectRatio = rhs.m_aspectRatio;
}

void Projection::Init(float aspectRatio, float nearPlane, float farPlane)
{
    if (nearPlane > farPlane)
    {
        throw std::invalid_argument("nearPlane value must be less than farPlane.");
    }

    m_near = nearPlane;
    m_far = farPlane;
    m_aspectRatio = aspectRatio;
}

glm::mat4 Projection::GetMatrix()
{
    return glm::perspective(60.0f, 1.0f / m_aspectRatio, m_near, m_far);
    //return MatrixHelper::CreateProjectionMatrix(1, m_aspectRatio, m_near, m_far);
}

float Projection::GetNearPlane()
{
    return m_near;
}

float Projection::GetFarPlane()
{
    return m_far;
}

float Projection::GetAspectRatio()
{
    return m_aspectRatio;
}
} // namespace trifle
