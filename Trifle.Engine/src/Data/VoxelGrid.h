#ifndef VOXELGRID_H
#define VOXELGRID_H

#include <glm/glm.hpp>
#include <vector>
#include <set>
#include <stdexcept>
#include "../Core/Types.h"

#include "../Util/Util.h"
#include "UIntPoint3.h"


namespace tfl
{

class VoxelGridCell
{
  private:
    unsigned int m_id;
    UIntPoint3 m_pos;
    Colour m_colour;

  public:
    unsigned int GetId()
    {
        return m_id;
    }

    void SetId(unsigned int value)
    {
        m_id = value;
    }

    UIntPoint3 GetPosition()
    {
        return m_pos;
    }

    void SetPosition(UIntPoint3 value)
    {
        m_pos = value;
    }

    Colour GetColour()
    {
        return m_colour;
    }

    void SetColour(Colour value)
    {
        m_colour = value;
    }

    VoxelGridCell()
    {
        m_id = 0;
        m_pos = UIntPoint3{0, 0, 0};
        m_colour = glm::vec4(0, 0, 0, 0);
    }
};

template <typename T>
class VoxelGrid
{
  private:
    unsigned int m_id;
    UIntPoint3 m_position;
    unsigned int m_size;

    unsigned int m_width, m_height, m_depth;

    std::vector<T> m_data;
    std::set<unsigned int> m_litVoxels;

  protected:
  public:
    /// @brief Constructor
    VoxelGrid()
    {
        static_assert(std::is_base_of<VoxelGridCell, T>::value, "type parameter of this method must be of type <tfl::VoxelGridCell>");
        m_litVoxels = {};
    }

    /// @brief Destructor
    ~VoxelGrid()
    {
        m_data.clear();
    }

    /// @brief Initialises the voxel grid with the provided dimensions
    /// @param width Grid size in the X axis
    /// @param height Grid size in the Y axis
    /// @param depth Grid size in the Z axis
    void Init(unsigned int width, unsigned int height, unsigned int depth)
    {
        m_data.clear();

        m_width = width;
        m_height = height;
        m_depth = depth;

        m_size = m_width * m_height * m_depth;

        m_data.resize(m_size);

        for (unsigned int i = 0; i < m_data.size(); i++)
        {
            UIntPoint3 point = VoxelGridUtil::GetUIntPoint3ByIndex(i, m_width, m_height, m_depth);

            VoxelGridCell* cell = (VoxelGridCell*)&m_data[i];
            cell->SetId(i);
            cell->SetPosition(point);
        }
    }

    /// @brief Checks to see if the grid contains a voxel for a given point
    /// @param point 
    /// @return Does the grid contain this point? (true/false)
    bool Contains(const UIntPoint3& point)
    {
        if (point.x > m_width || point.y > m_height || point.z > m_depth)
        {
            return false;
        }

        unsigned int idx = VoxelGridUtil::GetIndexByUIntPoint3(point, m_width, m_height, m_depth);
        return idx < m_data.size();
    }
    
    /// @brief Gets the voxel grid cell for the point provided.
    /// @param point 
    /// @return A pointer to the grid cell.
    T* GetCell(const UIntPoint3& point)
    {
        if (point.x > m_width || point.y > m_height || point.z > m_depth)
        {
            throw std::out_of_range("point coordinates exceeded grid dimensions.");
        }

        return &m_data[VoxelGridUtil::GetIndexByUIntPoint3(point, m_width, m_height, m_depth)];
    }

    T* GetCell(unsigned int idx)
    {
        return &m_data[idx];
    }
    
    /// @brief Gets all voxels that have been 'lit' (Voxels with a colour whose alpha is > 0)
    /// @return A vector of all lit cells
    std::vector<T*> GetPaintedCells()
    {
        std::vector<T*> result;
        result.reserve(m_litVoxels.size());

        std::set<unsigned int>::reverse_iterator it;

        for (it = m_litVoxels.rbegin(); it != m_litVoxels.rend(); it++)
        {
            result.push_back(GetCell(*it));
        }
        
        return result;
    }

    /// @brief Paints the grid cell at the given point with the specified colour.
    /// @param point Cell coordinate.
    /// @param colour Cell Colour.
    void PaintCell(const UIntPoint3 point, Colour colour)
    {
        unsigned int idx = VoxelGridUtil::GetIndexByUIntPoint3(point, m_width, m_height, m_depth);

        if (colour.a > 0.0f)
        {
            m_litVoxels.insert(idx);
        }
        else 
        {
            m_litVoxels.erase(idx);
        }

        m_data[idx].SetColour(colour);
    }

    /// @brief Will paint the grid cell at the given point and all surrounding cells to the specified colour. 
    /// @param point Cell cordinate.
    /// @param brushSize The number of surrounding voxels to paint.
    /// @param fillColour Cell Colour.
    void PaintCells(const UIntPoint3 point, unsigned int brushSize, Colour fillColour)
    {
        UIntPoint3 startPoint = {point.x - brushSize, point.y - brushSize, point.z - brushSize};
        UIntPoint3 endPoint = {point.x + brushSize, point.y + brushSize, point.z + brushSize};

        for (unsigned int x = startPoint.x; x < endPoint.x; x++)
        {
            for (unsigned int y = startPoint.y; y < endPoint.y; y++)
            {
                for (unsigned int z = startPoint.z; z < endPoint.z; z++)
                {
                    PaintCell({x, y, z}, fillColour);
                }
            }
        }
    }

    void Clear()
    {
        std::set<unsigned int>::iterator it;

        for (it = m_litVoxels.begin(); it != m_litVoxels.end(); it++)
        {
            m_data[*it].SetColour({0,0,0,0});
        }
    }

    unsigned int GetSize()
    {
        return m_size;
    }

    unsigned int GetWidth()
    {
        return m_width;
    }

    unsigned int GetHeight()
    {
        return m_height;
    }

    unsigned int GetMemorySize()
    {
        return (m_size * sizeof(T)) + sizeof(*this);
    }
};

} // namespace tfl

#endif // !VOXELGRID_H