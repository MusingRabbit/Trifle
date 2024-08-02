#pragma once

#include <glm/glm.hpp>
#include <gtest/gtest.h>

//#include "../../GTestHelper.h"

#include <trifle.h>
#include "../../GTestHelper.h"

using namespace tfl;


TEST(KDTree, KNearestNeighbours)
{
    
    KDTree tree = KDTreeTestHelper::CreateTree();
    std::vector<KDNode> result = tree.KNearestNeighbours({8,3}, 3);

    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0].pos[0], 8);
    ASSERT_EQ(result[0].pos[1], 3);
    ASSERT_EQ(result[1].pos[0], 7);
    ASSERT_EQ(result[1].pos[1], 3);
    ASSERT_EQ(result[2].pos[0], 7);
    ASSERT_EQ(result[2].pos[1], 3);
}

TEST(KDTree, KNearestNeighbours_WithPredicate)
{
    CoordPos testPoint = {8,3};
    KDTree tree = KDTreeTestHelper::CreateTree();
    std::vector<KDNode> allNodes = tree.GetAllNodes();

    struct TestPredicate : KDNodePredicate {
        CoordPos point;
        TestPredicate(CoordPos p) {
            this->point = p;
        }
        // only search for points with smaller y-coordinate
        bool operator()(const KDNode& kn) const {
        return this->point[1] > kn.pos[1];
        }
    };
    TestPredicate pred(testPoint);

    // 3 Nearest neighbours with a smaller y coordinate.
    std::vector<KDNode> result =  tree.KNearestNeighbours(testPoint, 3, &pred);

    ASSERT_EQ(result[0].pos[0], 7);
    ASSERT_EQ(result[0].pos[1], 2);
    ASSERT_EQ(result[1].pos[0], 2);
    ASSERT_EQ(result[1].pos[1], 1);
    ASSERT_EQ(result[2].pos[0], 1);
    ASSERT_EQ(result[2].pos[1], 2);
}

TEST(KDTree, RangeNearestNeighbours)
{
    CoordPos testPoint = {8,2};
    KDTree tree = KDTreeTestHelper::CreateTree();
    std::vector<KDNode> allNodes = tree.GetAllNodes();

    // Points with range <= 1.1
    std::vector<KDNode> result = tree.RangeNearestNeighbours(testPoint, 1.1);

    //Expected neighbours of 8.2 are 7.2 and 8.3
    ASSERT_EQ(result[0].pos[0], 7);
    ASSERT_EQ(result[0].pos[1], 2);
    ASSERT_EQ(result[1].pos[0], 8);
    ASSERT_EQ(result[1].pos[1], 3);

}


TEST(KDTree, RangeNearestNeighbours_MaxDistance)
{
    CoordPos testPoint = {8,2};
    KDTree tree = KDTreeTestHelper::CreateTree(0);
    std::vector<KDNode> allNodes = tree.GetAllNodes();

    // Points with range <= 1.1
    std::vector<KDNode> result = tree.RangeNearestNeighbours(testPoint, 1.1);

    //Expected neighbours of 7.2, 7.3, 8.3 


}