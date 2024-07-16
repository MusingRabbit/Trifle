#ifndef VOXELGRIDHELPER_H
#define VOXELGRIDHELPER_H

#include <array>
#include <glm/glm.hpp>

#include "../Data/UIntPoint3.h"

#define VOXEL_BLOCK_POINT_COUNT = 27;

namespace tfl
{
class VoxelGridUtil
{
  public:
    inline static unsigned int GetIndexByUIntPoint3(const UIntPoint3& point, unsigned int width, unsigned int height, unsigned int depth)
    {
        return point.x + (point.y * width) + (point.z * (width * height));
    }

    inline static UIntPoint3 GetUIntPoint3ByIndex(unsigned int index, unsigned int width, unsigned int height, unsigned int depth)
    {
        unsigned int z = index / (width * height);
        unsigned int y = (index - (z * width * height)) / width;
        unsigned int x = index % width;
        return UIntPoint3{x, y, z};
    }

    inline static UIntPoint3 Vec3ToUintPoint3(const glm::vec3& val)
    {
        return UIntPoint3 { (unsigned int)roundf(val.x), (unsigned int)roundf(val.y), (unsigned int)roundf(val.z)};
    }

    inline static glm::vec3 UIntPoint3ToVec3(const UIntPoint3& val)
    {
        return glm::vec3 { val.x, val.y, val.z };
    }
};
} // namespace tfl

#endif // !VOXELGRIDHELPER_H