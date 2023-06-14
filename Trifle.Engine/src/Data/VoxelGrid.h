#ifndef VOXELGRID_H
#define VOXELGRID_H

#include <glm/glm.hpp>
#include <vector>

#include "../Util/VoxelGridHelper.h"
#include "GridPoint.h"

namespace trifle
{

struct VoxelGridCell
{
    unsigned int Id;
    GridPoint Position;
    glm::vec4 Colour;

    VoxelGridCell()
    {
        Id = 0;
        Position = GridPoint(0, 0, 0);
        Colour = glm::vec4(0, 0, 0, 0);
    }
};

class VoxelGrid
{
  private:
    unsigned int m_id;
    GridPoint m_position;
    unsigned int m_size;
    unsigned int m_totalDataSize;
    std::vector<VoxelGridCell> m_data;

    unsigned int GetIndexByGridPoint(const GridPoint& point)
    {
        return VoxelGridHelper::GetIndexByGridPoint(point, m_size, m_size, m_size);
    }

  protected:
  public:
    /// @brief Constructor
    VoxelGrid()
    {
    }

    /// @brief Destructor
    ~VoxelGrid()
    {
    }

    void Initialise(unsigned int gridSize)
    {
        Clear();

        m_size = gridSize;
        m_totalDataSize = m_size * m_size * m_size;

        m_data.resize(m_totalDataSize);

        for (unsigned int z = 0; z < m_size; z++)
        {
            for (unsigned int y = 0; y < m_size; y++)
            {
                for (unsigned int x = 0; x < m_size; x++)
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

    VoxelGridCell* GetCell(const GridPoint& point)
    {
        return &m_data[GetIndexByGridPoint(point)];
    }

    unsigned int GetGridSize()
    {
        return m_size;
    }

    unsigned int GetTotalSize()
    {
        return m_totalDataSize;
    }

    void Clear()
    {
        m_data.clear();
    }
};

} // namespace trifle

#endif // !VOXELGRID_H