#ifndef VOXELENTITIY_H
#define VOXELENTITIY_H

#include "../Core/Core.h"
#include <glm/glm.hpp>

namespace tfl
{
class VoxelEntity : public Entity
{
    private:
/*     void NotifyPositionChanged(const glm::vec3& oldVal, const glm::vec3& newVal);
    void NotifyRotationChanged(const glm::vec3& oldVal, const glm::vec3& newVal);
    void NotifyScaleChanged(const glm::vec3& oldSize, const glm::vec3& newSize);
    void OnTransformChangedCallback(EventArgs& e); */

    public :
/*     EventHandler OnPositionChanged = {};
    EventHandler OnRotationChanged = {};
    EventHandler OnSizeChanged = {}; */
    
    VoxelEntity();
    VoxelEntity(const VoxelEntity& rhs);
    ~VoxelEntity();

    void Init();

    void SetPosition(glm::vec3 position);
    
    Point3 GetPoint();
    void SetPoint(Point3 point);

    void Move(const glm::vec3& moveVector);
    
    void Rotate(const glm::vec3& rotationVector);
    void SetColour(const Colour& colour);
    Colour GetColour();

    unsigned int GetSize();
};
}

#endif