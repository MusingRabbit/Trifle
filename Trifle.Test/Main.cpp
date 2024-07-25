#include <gtest/gtest.h>
#include "Tests/Core/Test.h"

using namespace tfl;

int main(int argc, char** argv)
{
    srand((unsigned int)time(0));
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::GTEST_FLAG(filter) = "VoxelGrid*";
    return RUN_ALL_TESTS();
}