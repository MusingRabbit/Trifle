#ifndef VOXELCHUNK_H
#define VOXELCHUNK_H

#include "VoxelGrid.h"

#include <Data/Point3.h>

namespace tfl
{
    class VoxelChunk 
    {
        private : 
            UIntPoint3 m_pos;
            Point3 m_gPos;
            Point3 m_max;
            VoxelGrid<VoxelGridCell> m_grid;

            unsigned int m_size;
            int m_multiplier;

        public :
            VoxelChunk();

            void Init(const UIntPoint3& position, const Point3& globalPosition, unsigned int size);

            unsigned int GetSize();

            VoxelGrid<VoxelGridCell>* GetGrid();

            UIntPoint3 GetLocalPosition();

            Point3 GetPosition();
            Point3 GetPosPlusX();
            Point3 GetPosPlusY();
            Point3 GetPosPlusZ();
            Point3 GetPosPlusSize();
            Point3 GetCentre();
            bool Contains(Point3 pos);

            void Fill(glm::vec4 colour);
    };
}

#endif