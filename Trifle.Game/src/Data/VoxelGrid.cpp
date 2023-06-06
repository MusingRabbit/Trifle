#include "VoxelGrid.h"
#include <stdexcept>

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

    for (unsigned int i = 0; i < m_totalDataSize; i ++)
    {
        m_data[i].Id = i;
        m_data[i].Position = GetGridPointByIndex(i);
    }
}

GridPoint VoxelGrid::GetGridPointByIndex(unsigned int index)
{
    if (index > m_totalDataSize){
        throw std::out_of_range("specified index is greated than the total grid size.");
    }
    
    // Calculate coordinates from a given index.
    // Row major order
    unsigned int z = index % m_size;
    unsigned int y = (index / m_size) % m_size;
    unsigned int x = index / (m_size * m_size);
    
    return GridPoint(x,y,z);
}

unsigned int VoxelGrid::GetIndexByGridPoint(GridPoint& point)
{
    return (point.X * m_size) + (point.Y * m_size) + (point.Z * m_size);
}

void VoxelGrid::Clear()
{
    if (m_data != nullptr){
        delete m_data;
        m_data = nullptr;
    }

    m_size = 0;
}
