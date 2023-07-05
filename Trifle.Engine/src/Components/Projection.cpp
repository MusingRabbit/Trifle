#include "Projection.h"

#include "../Util/Util.h"

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
    m_near = nearPlane;
    m_far = farPlane;
    m_aspectRatio = aspectRatio;
}

glm::mat4 Projection::GetPerspectiveMatrix()
{
    return MatrixHelper::CreatePerspectiveMatrix(1, m_aspectRatio, m_near, m_far);
}
} // namespace trifle
