#ifndef PROJECTION_H
#define PROJECTION_H

#include <glm/glm.hpp>

namespace trifle
{
class Projection
{
  private:
    float m_near;
    float m_far;
    float m_aspectRatio;

  public:
    Projection();
    Projection(float aspectRatio, float nearPlane, float farPlane);
    ~Projection();
    Projection(const Projection& rhs);

    void Init(float aspectRatio, float nearPlane, float farPlane);
    glm::mat4 GetPerspectiveMatrix();
};
} // namespace trifle

#endif // !PROJECTION_H
