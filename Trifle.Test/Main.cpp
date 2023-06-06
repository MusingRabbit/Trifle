#include <gtest/gtest.h>

void EmptyTest(){
    
} 

TEST(Empty_Test, EMPTY_TEST){
    
    ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}