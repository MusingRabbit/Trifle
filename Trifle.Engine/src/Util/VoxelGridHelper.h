#ifndef VOXELGRIDHELPER_H
#define VOXELGRIDHELPER_H

#include "../Data/VoxelGrid.h"

class VoxelGridHelper
{
public:
    inline static unsigned int GetIndexByGridPoint(GridPoint& point, unsigned int width, unsigned int height, unsigned int depth)
    {
        return point.X + (point.Y * width) + (point.Z * width * height);
    }
};

#endif // !VOXELGRIDHELPER_H