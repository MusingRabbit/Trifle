#ifndef VOXELGRIDCELL_H
#define VOXELGRIDCELL_H

#include "../Data/Data.h"
#include "../Core/Types.h"
#include "../Components/Transform.h"

namespace tfl
{
    class VoxelGridCell
    {
    private:
        unsigned int m_id;
        UIntPoint3 m_pos;
        Colour m_colour;

    public:
        VoxelGridCell();
        VoxelGridCell(const VoxelGridCell& rhs);

        unsigned int GetId();
        void SetId(unsigned int value);
        UIntPoint3 GetPosition();

        void SetPosition(UIntPoint3 value);
        Colour GetColour();
        Transform GetTransform();

        void SetColour(const Colour& value);
        void AppendColour(const Colour& value);
    };
}

#endif