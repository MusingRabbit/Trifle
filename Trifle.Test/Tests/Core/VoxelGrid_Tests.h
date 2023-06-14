#pragma Once
#include <gtest/gtest.h>

#include "../../GTestHelper.h"
#include <Data/VoxelGrid.h>
#include <chrono>
#include <iostream>

#define atoa(x) #x;

using namespace trifle;

const unsigned int GRID_SIZE = 343;

TEST(VoxelGrid, Grid_Initialisation)
{
    VoxelGrid grid;
    grid.Initialise(GRID_SIZE);
}

TEST(VoxelGrid, Grid_GetCell)
{
    VoxelGrid grid;
    grid.Initialise(GRID_SIZE);

    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned int z = 0; z < GRID_SIZE; z++)
    {
        for (unsigned int y = 0; y < GRID_SIZE; y++)
        {
            for (unsigned int x = 0; x < GRID_SIZE; x++)
            {
                VoxelGridCell* cell = grid.GetCell(GridPoint(x, y, z));
                float r = (x / GRID_SIZE) * 255;
                float g = (y / GRID_SIZE) * 255;
                float b = (z / GRID_SIZE) * 255;
                cell->Colour = glm::vec4(r, g, b, 1.0);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << COUT_GTEST_MGT << "Grid traversal took " << microseconds.count() << "ms" << ANSI_TXT_MGT << std::endl;
}