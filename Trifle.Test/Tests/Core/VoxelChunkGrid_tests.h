#pragma once

#include <gtest/gtest.h>
#include <trifle.h>
#include <glm/glm.hpp>


TEST(VoxelChunkGrid, Init)
{
    unsigned int gridSize = 1;
    unsigned int chunkSize = 16;

    VoxelChunkGrid grid;
    grid.Init(gridSize, chunkSize);

    ASSERT_TRUE(gridSize == grid.GetSize());
}


TEST(VoxelChunkGrid, GetChunk_ByGlobalPos)
{
    unsigned int gridSize = 3;
    unsigned int chunkSize = 3;

    VoxelChunkGrid grid;
    grid.Init(gridSize, chunkSize);

    VoxelChunk* chunk0 = grid.GetChunk(Point3(0,0,0));
    VoxelChunk* chunk1 = grid.GetChunk(Point3(5,2,0));          // Global Pos should be [1,0,0]
    VoxelChunk* chunk2 = grid.GetChunk(Point3(-1,3,0));
    VoxelChunk* chunk3 = grid.GetChunk(Point3(4,4,0));
    VoxelChunk* chunk4 = grid.GetChunk(Point3(-2,-2, 0));
    VoxelChunk* chunk6 = grid.GetChunk(Point3(1, 1, 1));

    Point3 pos0 = chunk0->GetPosition();
    Point3 pos1 = chunk1->GetPosition();
    Point3 pos2 = chunk2->GetPosition();
    Point3 pos3 = chunk3->GetPosition();
    Point3 pos4 = chunk4->GetPosition();
    Point3 pos6 = chunk6->GetPosition();

    ASSERT_TRUE(pos0 == Point3(0, 0, 0));
    ASSERT_TRUE(pos1 == Point3(1, 0, 0));
    ASSERT_TRUE(pos2 == Point3(0, 1, 0));
    ASSERT_TRUE(pos3 == Point3(1, 1, 0));
    ASSERT_TRUE(pos4 == Point3(0, 0, 0));
    ASSERT_TRUE(pos6 == Point3(0, 0, 0));
}


TEST(VoxelChunkGrid, FillChunk)
{
    unsigned int gridSize = 3;
    unsigned int chunkSize = 3;

    glm::vec4 fillColour = {1.0f, 0.0f, 1.0f, 1.0f};

    VoxelChunkGrid grid;
    grid.Init(gridSize, chunkSize);

    VoxelChunk* chunk = grid.GetChunk(0);
    chunk->Fill(fillColour);

    std::vector<VoxelGridCell*> cells = chunk->GetGrid()->GetCells(CellSortOrder::None);

    for (auto cell : cells)
    {
        ASSERT_TRUE(fillColour == cell->GetColour());
    }

}