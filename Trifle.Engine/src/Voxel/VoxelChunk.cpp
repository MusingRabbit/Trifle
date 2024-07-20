#include "VoxelChunk.h"

namespace tfl
{
    VoxelChunk::VoxelChunk()
    {
    }

    void VoxelChunk::Init(UIntPoint3 position, unsigned int size)
    {
        m_position = position;
        m_max = m_position + UIntPoint3(size, size, size);
        m_size = size;
        m_grid.Init(size, size, size);
        m_grid.Fill({1.0f, 1.0f, 1.0f, 1.0f});
    }

    unsigned int VoxelChunk::GetSize()
    {
        return m_size;
    }

    VoxelGrid<VoxelGridCell>* VoxelChunk::GetGrid()
    {
        return &m_grid;
    }

    UIntPoint3 VoxelChunk::GetPosition()
    {
        return m_position;
    }

    UIntPoint3 VoxelChunk::GetPosPlusX()
    {
        return {m_position.x + m_size, m_position.y, m_position.z};
    }

    UIntPoint3 VoxelChunk::GetPosPlusY()
    {
        return {m_position.x, m_position.y + m_size, m_position.z};
    }

    UIntPoint3 VoxelChunk::GetPosPlusZ()
    {
        return {m_position.x, m_position.y, m_position.z + m_size};
    }

    UIntPoint3 VoxelChunk::GetPosPlusSize()
    {
        return m_position + m_size;
    }

    UIntPoint3 VoxelChunk::GetCentre()
    {
        return (m_position + m_max) / (int)2;
    }

    bool VoxelChunk::Contains(UIntPoint3 pos)
    {
        return pos > m_position && pos < m_max;
    }

} // namespace tfl