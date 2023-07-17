#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include <glm/glm.hpp>

namespace tfl
{
class Collider
{
  private:
    bool m_recalculate;
    bool m_isTrigger;

    glm::vec3 m_max;
    glm::vec3 m_min;
    glm::vec3 m_size;
    glm::vec3 m_centre;

    void CalculateSize();
    void CalculateCentre();

  public:
    Collider();

    Collider(const Collider& rhs);
    ~Collider();

    bool IsEqual(const Collider& rhs);

    void SetRecalculate(bool value);
    bool GetRecalculate();

    void SetIsTrigger(bool value);
    bool GetIsTrigger();

    void SetMaximum(const glm::vec3& value);
    glm::vec3 GetMaximum();

    void SetMinimum(const glm::vec3& value);
    glm::vec3 GetMinimum();

    void SetCentre(float x, float y, float z);
    void SetCentre(const glm::vec3& value);
    glm::vec3 GetCentre();

    void SetScale(float value);

    void SetScale(const glm::vec3 value);

    bool Collides(const Collider& rhs);
};

} // namespace tfl

#endif // !COLLIDER_H