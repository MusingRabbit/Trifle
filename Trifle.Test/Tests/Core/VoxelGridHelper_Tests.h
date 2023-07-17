#pragma once

#include <trifle.h>

#include <gtest/gtest.h>
#include "../../GTestHelper.h"
#include <string>

using namespace tfl;

TEST(TrifleTest, GetIndexByPoint_Test)
{
    // SETUP : Create test data
    const unsigned int width = 5;
    const unsigned int height = 10;
    const unsigned int depth = 30;
    const unsigned int size = width * height * depth;

    bool indexFlags[size]{false}; // An bool array to ensure that the same index isn't hit twice.

    // Itterate through all dimensions
    for (unsigned int z = 0; z < depth; z++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            for (unsigned int x = 0; x < width; x++)
            {
                // Create new point
                UIntPoint3 point = UIntPoint3{x, y, z};

                // Get index result
                unsigned int result = VoxelGridUtil::GetIndexByUIntPoint3(point, width, height, depth);

                if (result >= size)
                {
                    // std::string strPoint = ("[x : " + x) + (", y : " + y) + ("z : " +
                    // z) + "]";
                    std::cout << "RESULT()" << result << ") >= SIZE(" << size << ")"
                              << " @ idx : " << x << std::endl;

                    bool b = false;
                }

                // Test result
                // Assert that the result index is not Out Of Range.
                ASSERT_LT(result, size);

                if (indexFlags[result] != false)
                {
                    std::cout << "RESULT()" << result << ") >= SIZE(" << size << ")" << std::endl;

                    bool b = false;
                }

                // All indexes should be unique - if the same index is hit twice, then
                // there is a problem.
                ASSERT_EQ(indexFlags[result], false);

                indexFlags[result] = true; // Mark the associted index flag as having been hit.
            }
        }
    }

    // Ensure that all indices were reached.
    for (unsigned int i = 0; i < size; i++)
    {
        ASSERT_TRUE(indexFlags[i]);
    }
}

TEST(TrifleTest, GetPointByIndex_Test)
{
    // SETUP : Create test data
    const unsigned int width = 10;
    const unsigned int height = 30;
    const unsigned int depth = 12;
    const unsigned int size = width * height * depth;

    unsigned int indices[size]{false}; // An bool array to ensure that the same index isn't hit twice.

    // Itterate through all dimensions
    for (unsigned int z = 0; z < depth; z++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            for (unsigned int x = 0; x < width; x++)
            {
                // Create new point
                UIntPoint3 point = UIntPoint3{x, y, z};
                unsigned int index = VoxelGridUtil::GetIndexByUIntPoint3(point, width, height, depth);
                UIntPoint3 newPoint = VoxelGridUtil::GetUIntPoint3ByIndex(index, width, height, depth);

                bool isMatch = newPoint.IsEqual(point);

                if (!isMatch)
                {
                    std::cout << COUT_GTEST_MGT << "Point mismatch @ [" << x << "," << y << "," << z << "]" << ANSI_TXT_MGT << std::endl;
                    newPoint = VoxelGridUtil::GetUIntPoint3ByIndex(index, width, height, depth);
                }

                ASSERT_TRUE(isMatch);
            }
        }
    }
}