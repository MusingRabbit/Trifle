#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include <queue>
#include <cstdlib>

#include "KDTreeNode.h"
#include "DistanceMeasure.h"

namespace tfl 
{
    // Internal classes used by the KdTree
    class KDTreeNode;                       // Internal node structure used by the KDTree     
    class DistanceMeasure;                  // Base class for different distance calculations

    class NN4Heap 
    {
        public:
        size_t dataIndex;       //  index of actual KdNode in 'all nodes'
        double distance;        // distance of this neighbour from 'pos'
        
        NN4Heap(size_t i, double d)
        {
            dataIndex = i;
            distance = d;
        }
    };

    class CompareNN4Heap 
    {
        public : 
        bool operator()(const NN4Heap& rhs, const NN4Heap& lhs){
            return (rhs.distance < lhs.distance);
        }
    };

    //--------------------------------------------------------------
    // function object for comparing only dimension d of two vecotrs
    //--------------------------------------------------------------
    class CompareDimension
    {
        size_t d;

        public :
            CompareDimension(size_t dim)
            {
                d = dim;
            }

            bool operator()(const KDNode& lhs, const KDNode& rhs)
            {
                return lhs.pos[d] < rhs.pos[d];
            }
    };

    typedef std::priority_queue<NN4Heap, std::vector<NN4Heap>, CompareNN4Heap> SearchQueue;

    class KDTree
    {
        private:
        CoordPos m_loBound, m_hiBound;
        int m_distanceType;

        // Recursive tree build
        KDTreeNode* BuildTree(size_t depth, size_t a, size_t b);
        
        bool NeighbourSearch(const CoordPos& pos, KDTreeNode* node, size_t k, SearchQueue* neighbourHeap);
        void RangeSearch(const CoordPos& pos, KDTreeNode* node, double r, std::vector<size_t>* rangeResult);
        bool BoundsOverlapBall(const CoordPos& pos, double distance, KDTreeNode* node);
        bool BallWithinBounds(const CoordPos& pos, double distance, KDTreeNode* node);
        
        DistanceMeasure* m_distance;        // Class which implements distance computation
        KDNodePredicate* m_searchPredicate; // Class which will perform the search predicate...

        std::vector<KDNode> m_allNodes;
        size_t m_dimension;
        KDTreeNode* m_root;

        public:
        KDTree();
        KDTree(const KDTree& rhs);
        ~KDTree();


        void Clear();
        void Init(const std::vector<KDNode>& nodes, int distanceType = 2);
        void SetDistance(int distanceType, const std::vector<double>& weights);
        std::vector<KDNode> KNearestNeighbours(const CoordPos& pos, size_t k, KDNodePredicate* predicate = nullptr);
        std::vector<KDNode> RangeNearestNeighbours(const CoordPos& pos, double r);

        std::vector<KDNode> GetAllNodes();
    };
}




#endif