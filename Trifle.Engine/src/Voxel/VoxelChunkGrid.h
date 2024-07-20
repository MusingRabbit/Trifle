#ifndef VOXELCHUNKGRID_H
#define VOXELCHUNKGRID_H

#include "VoxelChunk.h"

namespace tfl 
{
    class VoxelChunkGrid
    {
        private:
            unsigned int m_id;
            unsigned int m_size;
            unsigned int m_chunkSize;

            unsigned int m_width, m_height, m_depth;

            std::vector<VoxelChunk> m_chunks;

        public:
            VoxelChunkGrid() 
            {

            }

            ~VoxelChunkGrid()
            {

            }

            /// @brief Initialises the voxel chunk grid
            /// @param gridSize The size of the grid itself. E.g 16 will create a 16x16x16 grid of chunks
            /// @param chunkSize The size of each chunk (in voxels) - The resolution
            void Init(unsigned int gridSize, unsigned int chunkSize)
            {
                m_width = gridSize;
                m_height = gridSize;
                m_depth = gridSize;

                m_chunkSize = chunkSize;

                unsigned int m_size = m_width * m_height * m_depth;

                m_chunks.resize(m_size);

                for (unsigned int i = 0; i < m_chunks.size(); i++)
                {
                    UIntPoint3 point = VoxelGridUtil::GetUIntPoint3ByIndex(i, m_width, m_height, m_depth);
                    VoxelChunk* chunk = (VoxelChunk*)&m_chunks[i];
                    chunk->Init(point, chunkSize);
                }
            }

            unsigned int GetChunkSize()
            {
                return m_chunkSize;
            }

            unsigned int GetSize()
            {
                return (m_width + m_height + m_depth) / 3;
            }

            void Clear()
            {
                for (unsigned int i = 0; i < m_chunks.size(); i++)
                {
                    VoxelChunk* chunk = (VoxelChunk*)&m_chunks[i];
                    chunk->GetGrid()->Clear();
                }
            }

            void FillChunk(UIntPoint3 pos, glm::vec4 colour)
            {
                GetChunk(pos)->GetGrid()->Fill(colour);
            }
            
            VoxelChunk* FindChunkByGlobalPos(const UIntPoint3& globalPos)
            {
                UIntPoint3 pos = globalPos / UIntPoint3(m_width, m_height, m_depth);
                return GetChunk(pos);
            }

            /// @brief Itterates through the grid to determine which cells are visible
            bool IsChunkVisible(VoxelChunk* cell)
            {
                UIntPoint3 pos = cell->GetPosition();
                
                VoxelChunk* north = GetChunk({pos.x, pos.y, pos.z + 1});
                VoxelChunk* south = GetChunk({pos.x, pos.y, pos.z - 1});
                VoxelChunk* east = GetChunk({pos.x + 1, pos.y, pos.z});
                VoxelChunk* west = GetChunk({pos.x - 1, pos.y, pos.z});
                VoxelChunk* up = GetChunk({pos.x, pos.y + 1, pos.x});
                VoxelChunk* down = GetChunk({pos.x, pos.y - 1, pos.x});

                bool isCovered = 
                north == nullptr && 
                south == nullptr && 
                east == nullptr &&
                west == nullptr && 
                up == nullptr &&
                down == nullptr;

                return isCovered == false;
            }

            std::vector<VoxelChunk*> GetVisibleChunks()
            {
                std::set<unsigned int>::iterator it;
                std::vector<VoxelChunk*> result = {};

                for (unsigned int i = 0; i < m_chunks.size(); i++)
                {
                    VoxelChunk* chunk = GetChunk(i);

                    if (IsChunkVisible(chunk))
                    {
                        result.push_back(chunk);
                    }
                }

                return result;
            }

            /// @brief Gets the voxel grid cell for the point provided.
            /// @param point 
            /// @return A pointer to the grid cell.
            VoxelChunk* GetChunk(const UIntPoint3& point)
            {
                if (point.x > m_width || point.y > m_height || point.z > m_depth)
                {
                    //throw std::out_of_range("point coordinates exceeded grid dimensions.");
                    return nullptr;
                }

                return &m_chunks[VoxelGridUtil::GetIndexByUIntPoint3(point, m_width, m_height, m_depth)];
            }

            VoxelChunk* GetChunk(unsigned int idx)
            {
                if (idx < 0 || idx > m_size)
                {
                    return nullptr;
                }

                return &m_chunks[idx];
            }
        };
}

#endif