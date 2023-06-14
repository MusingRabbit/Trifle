#ifndef VOXELGRIDHELPER_H
#define VOXELGRIDHELPER_H

#include "../Data/GridPoint.h"

namespace trifle
{
class VoxelGridHelper
{
  public:
    inline static unsigned int GetIndexByGridPoint(const GridPoint& point, unsigned int width, unsigned int height,
                                                   unsigned int depth)
    {
        return point.X + (point.Y * width) + (point.Z * width * height);
    }
};
} // namespace trifle

#endif // !VOXELGRIDHELPER_H