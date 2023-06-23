#ifndef VOXELGRIDHELPER_H
#define VOXELGRIDHELPER_H

#include "../Data/UIntPoint3.h"

namespace trifle
{
class VoxelGridHelper
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
};
} // namespace trifle

#endif // !VOXELGRIDHELPER_H