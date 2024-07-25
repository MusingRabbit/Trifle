#include "VoxelChunkGrid.h"

namespace tfl 
{
    void VoxelChunkGrid::Init(unsigned int gridSize, unsigned int chunkSize)
    {
        m_width = gridSize;
        m_height = gridSize;
        m_depth = gridSize;

        m_chunkSize = chunkSize;

        unsigned int m_size = m_width * m_height * m_depth;

        m_centre = {(int)m_width / 2, (int)m_height / 2, (int)m_depth / 2};
        m_gCentre = {0, 0, 0};
        m_gOffset = m_gCentre - m_centre;

        m_chunks.resize(m_size);

        for (unsigned int i = 0; i < m_chunks.size(); i++)
        {
            UIntPoint3 localPos = VoxelGridUtil::GetUIntPoint3ByIndex(i, m_width, m_height, m_depth);
            Point3 globalPos = GetChunkGlobalPosition(localPos);
            VoxelChunk* chunk = (VoxelChunk*)&m_chunks[i];
            chunk->Init(localPos, globalPos, chunkSize);
        }
    }

    Point3 VoxelChunkGrid::GetGlobalOffset(bool negative)
    {
        Point3 result;
        result.x = negative ? -(int)m_width / 2 : (int)m_width / 2;
        result.y = negative ? -(int)m_height / 2 : (int)m_height / 2; 
        result.z = negative ? -(int)m_depth / 2 : (int)m_depth / 2;
        return result;
    }

    unsigned int VoxelChunkGrid::GetChunkSize()
    {
        return m_chunkSize;
    }

    unsigned int VoxelChunkGrid::GetSize()
    {
        return (m_width + m_height + m_depth) / 3;
    }

    void VoxelChunkGrid::Clear()
    {
        for (unsigned int i = 0; i < m_chunks.size(); i++)
        {
            VoxelChunk* chunk = (VoxelChunk*)&m_chunks[i];
            chunk->GetGrid()->Clear();
        }
    }

    bool VoxelChunkGrid::IsChunkVisible(VoxelChunk* cell) 
    {
        UIntPoint3 pos = cell->GetLocalPosition();
        
        VoxelChunk* north = GetChunk(Point3(pos.x, pos.y, pos.z + 1));
        VoxelChunk* south = GetChunk(Point3(pos.x, pos.y, pos.z - 1));
        VoxelChunk* east = GetChunk(Point3(pos.x + 1, pos.y, pos.z));
        VoxelChunk* west = GetChunk(Point3(pos.x - 1, pos.y, pos.z));
        VoxelChunk* up = GetChunk(Point3(pos.x, pos.y + 1, pos.x));
        VoxelChunk* down = GetChunk(Point3(pos.x, pos.y - 1, pos.x));

        bool isCovered = 
        north == nullptr && 
        south == nullptr && 
        east == nullptr &&
        west == nullptr && 
        up == nullptr &&
        down == nullptr;

        return isCovered == false;
    }

    std::vector<VoxelChunk*> VoxelChunkGrid::GetAllChunksByRange(Point3 globalPosition, unsigned int size)
    {
        return GetChunksByRange(globalPosition, size, false);
    }

    std::vector<VoxelChunk*> VoxelChunkGrid::GetChunksByRange(Point3 globalPosition, unsigned int size, bool filterEmpty)
    {
        std::set<unsigned int>::iterator it;
        std::vector<VoxelChunk*> result = {};

        for (unsigned int i = 0; i < m_chunks.size(); i++)
        {
            VoxelChunk* chunk = this->GetChunk(i);

            if (filterEmpty && !chunk->GetGrid()->HasPaintedCells())
            {
                continue;
            }

            Point3 pos = chunk->GetPosition();
            Point3 dPos = pos - globalPosition;

            if (dPos < Point3(size, size, size))
            {
                result.push_back(chunk);
            }
        }

        return result;
    }

    VoxelChunk* VoxelChunkGrid::GetChunk(const UIntPoint3& point)
    {
        if (point.x > m_width || point.y > m_height || point.z > m_depth)
        {
            //throw std::out_of_range("point coordinates exceeded grid dimensions.");
            return nullptr;
        }

        return  &m_chunks[VoxelGridUtil::GetIndexByUIntPoint3(point, m_width, m_height, m_depth)];
    }

    VoxelChunk* VoxelChunkGrid::GetChunk(unsigned int idx)
    {
        if (idx < 0 || idx > m_size)
        {
            return nullptr;
        }

        return &m_chunks[idx];
    }

    VoxelChunk* VoxelChunkGrid::GetChunk(const Point3& globalPos)
    {
        Point3 offsetPos = globalPos - m_gOffset;
        Point3 pos = (Point3(offsetPos.x / (int)m_chunkSize, offsetPos.y / (int)m_chunkSize, offsetPos.z / (int)m_chunkSize));

        return GetChunk(UIntPoint3((unsigned int)pos.x, (unsigned int)pos.y, (unsigned int)pos.z));
    }

    Point3 VoxelChunkGrid::GetChunkGlobalPosition(const UIntPoint3& localPos)
    {
        Point3 offsetPos = Convert::ToPoint3(localPos) + m_gOffset;
        return (Point3(offsetPos.x * (int)m_chunkSize, offsetPos.y * (int)m_chunkSize, offsetPos.z * (int)m_chunkSize));
    }

} // namespace tfl
