#pragma once
#include <gtest/gtest.h>

#include "../../GTestHelper.h"
#include <chrono>
#include <iostream>

#include <trifle.h>

#define atoa(x) #x;

using namespace tfl;

const unsigned int LARGE_GRID_SIZE = 343;

TEST(VoxelGrid, Grid_Initialisation)
{
    VoxelGrid<VoxelGridCell> grid;
    grid.Init(LARGE_GRID_SIZE, LARGE_GRID_SIZE, LARGE_GRID_SIZE);
}

TEST(VoxelGrid, Grid_GetCell)
{
    VoxelGrid<VoxelGridCell> grid;
    grid.Init(LARGE_GRID_SIZE, LARGE_GRID_SIZE, LARGE_GRID_SIZE);

    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned int z = 0; z < LARGE_GRID_SIZE; z++)
    {
        for (unsigned int y = 0; y < LARGE_GRID_SIZE; y++)
        {
            for (unsigned int x = 0; x < LARGE_GRID_SIZE; x++)
            {
                VoxelGridCell* cell = grid.GetCell({x, y, z});
                float r = (x / LARGE_GRID_SIZE) * 255;
                float g = (y / LARGE_GRID_SIZE) * 255;
                float b = (z / LARGE_GRID_SIZE) * 255;
                cell->SetColour(Colour(r, g, b, 1.0));
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << COUT_GTEST_MGT << "Grid size : " << grid.GetMemorySize() << " bytes" << ANSI_TXT_DFT << std::endl;
    std::cout << COUT_GTEST_MGT << "Grid traversal took : " << microseconds.count() << "ms" << ANSI_TXT_DFT << std::endl;
}

TEST(VoxelGrid, Grid_Fill)
{
    VoxelGrid<VoxelGridCell> grid;
    grid.Init(16, 16, 16);

    glm::vec4 tstColour = {0.0f, 1.0f, 0.0f, 1.0f};

    grid.Fill(tstColour);

    bool colourNotFound = false;

    for (unsigned int z = 0; z < 16; z++)
    {
        for (unsigned int y = 0; y < 16; y++)
        {
            for (unsigned int x = 0; x < 16; x++)
            {
                colourNotFound = grid.GetCell({x,y,z})->GetColour() != tstColour;

                if (colourNotFound)
                    break;
            }
            if (colourNotFound)
                break;
        }
        if (colourNotFound)
            break;
    }


    ASSERT_FALSE(colourNotFound);
}

TEST(VoxelGrid, Grid_GetVisibleCells)
{
    VoxelGrid<VoxelGridCell> grid;
    grid.Init(LARGE_GRID_SIZE, LARGE_GRID_SIZE, LARGE_GRID_SIZE);

    grid.PaintCell({60, 99, 104}, {1, 1, 1, 1});
    grid.PaintCell({46, 342, 100}, {1, 1, 1, 1});
    grid.PaintCell({64, 140, 203}, {1, 1, 1, 1});
    grid.PaintCell({47, 100, 102}, {1, 1, 1, 1});
    grid.PaintCell({6, 54, 103}, {1, 1, 1, 1});

    std::vector <VoxelGridCell*> cells = grid.GetVisibleCells();

    int cellCount = cells.size();
    ASSERT_TRUE(cellCount == 5);

    UIntPoint3 pos0 = cells[0]->GetPosition();
    UIntPoint3 pos1 = cells[1]->GetPosition();
    UIntPoint3 pos2 = cells[2]->GetPosition();
    UIntPoint3 pos3 = cells[3]->GetPosition();
    UIntPoint3 pos4 = cells[4]->GetPosition();

    ASSERT_TRUE(pos0 == UIntPoint3(46, 342, 100));
    ASSERT_TRUE(pos1 == UIntPoint3(47, 100, 102));
    ASSERT_TRUE(pos2 == UIntPoint3(6, 54, 103));
    ASSERT_TRUE(pos3 == UIntPoint3(60, 99, 104));
    ASSERT_TRUE(pos4 == UIntPoint3(64, 140, 203));
}

TEST(VoxelGrid, Grid_GetVisibleCells_Hidden)
{
    VoxelGrid<VoxelGridCell> grid;
    grid.Init(3,3,3);

    grid.Fill({1,1,1,1});                   
    grid.PaintCell({1,1,1}, {1,0,0,1});     //Centre Voxel - should be hidden

    std::vector<VoxelGridCell*> cells = grid.GetVisibleCells();
    
    int cellCount = cells.size();

    ASSERT_TRUE(cellCount == 26);

    bool found = false;

    for (unsigned int i = 0; i < cells.size(); i++)
    {
        if (cells[i]->GetColour() == Colour(1.0f, 0.0f ,0.0f ,1.0f))
        {
            found = true;
        }
    }

    ASSERT_FALSE(found);
}