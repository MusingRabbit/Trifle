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

            Point3 m_centre;
            Point3 m_gCentre;
            Point3 m_gOffset;

            std::vector<VoxelChunk> m_chunks;

            /// @brief Checks to see if a voxel can be seen
            /// @param chunk Chunk to be evaluated
            /// @return voxel visible? (true/false)
            bool IsChunkVisible(VoxelChunk* chunk);

            /// <summary>
            /// Gets the global offset
            /// </summary>
            /// <param name="negative"></param>
            /// <returns></returns>
            Point3 GetGlobalOffset(bool negative);

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
            void Init(unsigned int gridSize, unsigned int chunkSize); 

            /// @brief Transforms local grid position to global (world) position
            /// @param localPos Local position
            /// @return World position
            Point3 GetChunkGlobalPosition(const UIntPoint3& localPos);

            /// @brief Gets the size of each chunk
            /// @return Chunk size
            unsigned int GetChunkSize();
            
            /// @brief Gets the overall size of the grid (wxhxd)
            /// @return Grid size
            unsigned int GetSize();

            /// @brief Calls clear on every chunk within the grid.
            void Clear();

            /// @brief Gets all chunks within a specified range of the given position
            /// @param globalPosition World position    
            /// @param size Distance from centre (world position)
            /// @param filterEmpty if true, will get only chunks containing one or more lit voxels.
            /// @return A list of voxel chunks within range.
            std::vector<VoxelChunk*> GetChunksByRange(Point3 globalPosition, unsigned int size, bool filterEmpty);

            /// @brief Gets all chunks within a specified range of the given position.
            /// @param globalPosition 
            /// @param size 
            /// @return 
            std::vector<VoxelChunk*> GetAllChunksByRange(Point3 globalPosition, unsigned int size);

            /// @brief Gets a chunk by global / world position
            /// @param globalPos World position 
            /// @return Ptr to voxel chunk
            VoxelChunk* GetChunk(const Point3& globalPos);

            /// @brief Gets a voxel chunk for the local position specified
            /// @param point Local (Grid) position
            /// @return Ptr to voxel chunk
            VoxelChunk* GetChunk(const UIntPoint3& point);

            /// @brief Gets a chunk by specified index
            /// @param idx Grid index
            /// @return Ptr to voxel chunk
            VoxelChunk* GetChunk(unsigned int idx);
            
        };
}

#endif