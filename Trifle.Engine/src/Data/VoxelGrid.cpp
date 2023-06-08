#include "VoxelGrid.h"
#include <stdexcept>
#include "../Util/VoxelGridHelper.h"

VoxelGrid::VoxelGrid()
{
}

VoxelGrid::~VoxelGrid()
{
}

void VoxelGrid::Initialise(unsigned int gridSize)
{
    Clear();

    m_size = gridSize;

    m_totalDataSize = gridSize * gridSize * gridSize;

    m_data = new VoxelGridCell[m_totalDataSize];

    for (unsigned int z = 0; z < gridSize; z++)
    {
        for (unsigned int y = 0; y < gridSize; y ++)
        {
            for (unsigned int x = 0; x < gridSize; x++)
            {
                GridPoint point(x, y, z);
                unsigned int idx = GetIndexByGridPoint(point);

                VoxelGridCell* cell = &m_data[idx];
                cell->Id = idx;
                cell->Position = point;
            }
        }
    }
}

GridPoint VoxelGrid::GetGridPointByIndex(unsigned int index)
{
    if (index > m_totalDataSize){
        throw std::out_of_range("specified index is greated than the total grid size.");
    }
    
    return m_data[index].Position;
}

unsigned int VoxelGrid::GetIndexByGridPoint(GridPoint& point)
{
    return VoxelGridHelper::GetIndexByGridPoint(point, m_size, m_size, m_size);
}

unsigned int VoxelGrid::GetGridSize()
{
    return m_size;
}

unsigned int VoxelGrid::GetTotalSize()
{
    return m_totalDataSize;
}

void VoxelGrid::Clear()
{
    if (m_data != nullptr){
        delete m_data;
        m_data = nullptr;
    }

    m_size = 0;
}
