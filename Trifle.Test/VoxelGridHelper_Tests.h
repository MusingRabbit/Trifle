#ifndef VOXELHELPER_TESTS_H
#define VOXELHELPER_TESTS_H

#include <gtest/gtest.h>
#include <Util/VoxelGridHelper.h>
#include <string>


TEST(VoxelGridHelper, GetIndexByGridPoint_Test)
{
    // SETUP : Create test data
    unsigned int width = 5;
    unsigned int height = 10;
    unsigned int depth = 30;
    unsigned int size = width * height * depth;

    bool indexFlags[size] { false }; // An bool array to ensure that the same index isn't hit twice.

    // Itterate through all dimensions
    for (unsigned int z = 0; z < depth; z ++)
    {
        for (unsigned int y = 0; y < height; y ++)
        {
            for (unsigned int x = 0; x < width; x ++)
            {
                // Create new point
                GridPoint point = GridPoint(x, y, z);

                // Get index result
                unsigned int result = VoxelGridHelper::GetIndexByGridPoint(point, width, height, depth);

                if (result >= size)
                {
                    //std::string strPoint = ("[x : " + x) + (", y : " + y) + ("z : " + z) + "]";
                    std::cout << "RESULT()" << result << ") >= SIZE(" << size << ")" << " @ idx : " << x << std::endl;

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

                // All indexes should be unique - if the same index is hit twice, then there is a problem.
                ASSERT_EQ(indexFlags[result], false);

                indexFlags[result] = true; // Mark the associted index flag as having been hit.
            }
        }
    }

    // Ensure that all indices were reached.
    for (unsigned int i = 0; i < size; i++){
        ASSERT_TRUE(indexFlags[i]);
    }
}

#endif // VOXELHELPER_TESTS_H