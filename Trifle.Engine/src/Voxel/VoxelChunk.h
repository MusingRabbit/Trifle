#ifndef VOXELCHUNK_H
#define VOXELCHUNK_H

#include "VoxelGrid.h"

namespace tfl
{
    class VoxelChunk 
    {
        private : 
            UIntPoint3 m_position;
            UIntPoint3 m_max;
            VoxelGrid<VoxelGridCell> m_grid;

            unsigned int m_size;

        public :
            VoxelChunk();

            void Init(UIntPoint3 position, unsigned int size);

            unsigned int GetSize();

            VoxelGrid<VoxelGridCell>* GetGrid();

            UIntPoint3 GetPosition();

            UIntPoint3 GetPosPlusX();

            UIntPoint3 GetPosPlusY();

            UIntPoint3 GetPosPlusZ();

            UIntPoint3 GetPosPlusSize();

            UIntPoint3 GetCentre(); 

            bool Contains(UIntPoint3 pos);
    };
}

#endif