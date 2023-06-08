#ifndef VOXELCELL_H
#define VOXELCELL_H

#include <glm/glm.hpp>

struct GridPoint
{
    unsigned int X;
    unsigned int Y;
    unsigned int Z;
    
    GridPoint()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    GridPoint(unsigned int x, unsigned int y, unsigned int z)
    {
        X = x;
        Y = y;
        Z = z;
    }
};


struct VoxelGridCell 
{
    unsigned int Id;
    GridPoint Position;
    glm::vec4 Colour;

    VoxelGridCell()
    {
        
    }
};

class VoxelGrid 
{
    private:
    unsigned int m_id;
    GridPoint m_position;
    unsigned int m_size;
    unsigned int m_totalDataSize;
    VoxelGridCell* m_data;

    GridPoint GetGridPointByIndex(unsigned int index);
    unsigned int GetIndexByGridPoint(GridPoint& point);

    protected:
    public:
    /// @brief Constructor
    VoxelGrid();
    
    /// @brief Destructor
    ~VoxelGrid();

    void Initialise(unsigned int gridSize);

    VoxelGridCell* GetCell(GridPoint& point);

    unsigned int GetGridSize();
    unsigned int GetTotalSize();

    void Clear();
};


#endif // !VOXELCELL_H

