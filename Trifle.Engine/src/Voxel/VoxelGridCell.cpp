#include "VoxelGridCell.h"


namespace tfl 
{
    unsigned int VoxelGridCell::GetId()
    {
        return m_id;
    }

    void VoxelGridCell::SetId(unsigned int value)
    {
        m_id = value;
    }

    UIntPoint3 VoxelGridCell::GetPosition()
    {
        return m_pos;
    }

    void VoxelGridCell::SetPosition(UIntPoint3 value)
    {
        m_pos = value;
    }

    Colour VoxelGridCell::GetColour()
    {
        return m_colour;
    }

    Transform VoxelGridCell::GetTransform()
    {
        Transform result = {};

        result.SetPosition({(float)m_pos.x, (float)m_pos.y, (float)m_pos.z});
        result.Scale(1.0f);

        return result;
    }

    void VoxelGridCell::SetColour(const Colour& value)
    {
        m_colour.r = value.r;
        m_colour.g = value.g;
        m_colour.b = value.b;
        m_colour.a = value.a;
    }

    void VoxelGridCell::AppendColour(const Colour& value)
    {
        m_colour.r += value.r;
        m_colour.g += value.g;
        m_colour.b += value.b;
        m_colour.a += value.a;

        m_colour.r = (m_colour.r < 0) ? 0 : m_colour.r;
        m_colour.g = (m_colour.g < 0) ? 0 : m_colour.g;
        m_colour.b = (m_colour.b < 0) ? 0 : m_colour.b;
        m_colour.a = (m_colour.a < 0) ? 0 : m_colour.a;
    }

    VoxelGridCell::VoxelGridCell()
    {
        m_id = 0;
        m_pos = UIntPoint3{0, 0, 0};
        m_colour = glm::vec4(0, 0, 0, 0);
    }

    VoxelGridCell::VoxelGridCell(const VoxelGridCell& rhs)
    {
        m_id = rhs.m_id;
        m_pos = rhs.m_pos;
        m_colour = rhs.m_colour;
    }

} // namespace tfl