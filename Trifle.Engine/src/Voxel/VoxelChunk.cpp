#include "VoxelChunk.h"

namespace tfl
{
    VoxelChunk::VoxelChunk()
    {
    }

    void VoxelChunk::Init(const UIntPoint3& position, const Point3& globalPosition, unsigned int size)
    {
        m_pos = position;
        m_gPos = globalPosition;
        m_max = m_gPos + Point3(size, size, size);
        m_size = size;
        m_grid.Init(size, size, size);
        //m_grid.Fill({1.0f, 1.0f, 1.0f, 1.0f});
    }

    unsigned int VoxelChunk::GetSize()
    {
        return m_size;
    }

    VoxelGrid<VoxelGridCell>* VoxelChunk::GetGrid()
    {
        return &m_grid;
    }

    UIntPoint3 VoxelChunk::GetLocalPosition()
    {
        return m_pos;
    }

    Point3 VoxelChunk::GetPosition()
    {
        return m_gPos;
    }

    Point3 VoxelChunk::GetPosPlusX()
    {
        return {m_gPos.x + (int)m_size, m_gPos.y, m_gPos.z};
    }

    Point3 VoxelChunk::GetPosPlusY()
    {
        return {m_gPos.x, m_gPos.y + (int)m_size, m_gPos.z};
    }

    Point3 VoxelChunk::GetPosPlusZ()
    {
        return {m_gPos.x, m_gPos.y, m_gPos.z + (int)m_size};
    }

    Point3 VoxelChunk::GetPosPlusSize()
    {
        return m_gPos + m_size;
    }

    Point3 VoxelChunk::GetCentre()
    {
        return (m_gPos + m_max) / (int)2;
    }

    bool VoxelChunk::Contains(Point3 pos)
    {
        return pos > m_gPos && pos < m_max;
    }

    void VoxelChunk::Fill(glm::vec4 colour)
    {
        GetGrid()->Fill(colour);
    }

} // namespace tfl