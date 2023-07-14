#ifndef VOXELGRID_H
#define VOXELGRID_H

#include <glm/glm.hpp>
#include <vector>
#include <stdexcept>
#include "../Core/Types.h"

#include "../Util/Util.h"
#include "UIntPoint3.h"


namespace trifle
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

  protected:
  public:
    /// @brief Constructor
    VoxelGrid()
    {
        static_assert(std::is_base_of<VoxelGridCell, T>::value, "type parameter of this method must be of type <trifle::VoxelGridCell>");
    }

    /// @brief Destructor
    ~VoxelGrid()
    {
    }

    void Init(unsigned int width, unsigned int height, unsigned int depth)
    {
        Clear();

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

    bool Contains(const UIntPoint3& point)
    {
        if (point.x > m_width || point.y > m_height || point.z > m_depth)
        {
            return false;
        }

        unsigned int idx = VoxelGridUtil::GetIndexByUIntPoint3(point, m_width, m_height, m_depth);
        return idx < m_data.size();
    }

    T* GetCell(const UIntPoint3& point)
    {
        if (point.x > m_width || point.y > m_height || point.z > m_depth)
        {
            throw std::out_of_range("point coordinates exceeded grid dimensions.");
        }

        return &m_data[VoxelGridUtil::GetIndexByUIntPoint3(point, m_width, m_height, m_depth)];
    }

    void PaintCell(const UIntPoint3 point, Colour colour)
    {
        m_data[VoxelGridUtil::GetIndexByUIntPoint3(point, m_width, m_height, m_depth)].SetColour(colour);
    }

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

    void Clear()
    {
        m_data.clear();
    }
};

} // namespace trifle

#endif // !VOXELGRID_H