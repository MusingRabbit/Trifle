#include <gtest/gtest.h>
#include "Tests/Core/Test.h"

using namespace trifle;

int main(int argc, char** argv)
{
    srand((unsigned int)time(0));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}