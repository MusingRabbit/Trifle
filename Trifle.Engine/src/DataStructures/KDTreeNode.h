#ifndef KDTREENODE_H
#define KDTREENODE_H

#include <vector>
#include <any>

namespace tfl
{
    typedef std::vector<double> CoordPos; 

    class KDTreeNode
    {
        public : 

        // index of node data in kdtree array "allnodes"
        size_t dataindex;
        // cutting dimension
        size_t cutdim;
        // value of point
        // double cutval; // == point[cutdim]
        CoordPos pos;
        //  roots of the two subtrees
        KDTreeNode *childLo, *childHi;
        // bounding rectangle of this node's subtree
        CoordPos lobound, hiBound;

        KDTreeNode()
        {
            childLo = nullptr;
            childHi = nullptr;
        }

        ~KDTreeNode()
        {
            if (childLo != nullptr) 
            {
                delete childLo;
            }

            if (childHi != nullptr) 
            { 
                delete childHi; 
            }
        }

        double GetValue()
        {
            return pos[cutdim];
        }
    };

    // B-Tree operating on k-dimensions
    struct KDNode
    {
        CoordPos pos;
        std::any data;
        int idx;

        KDNode(const CoordPos& p, std::any d = nullptr, int i = -1)
        {
            pos = p;
            data = d;
            idx = i;
        }

        KDNode(const KDNode& rhs)
        {
            pos = rhs.pos;
            data = rhs.data;
            idx = rhs.idx;
        }

        KDNode()
        {
            data = NULL;
        }
    };

    /// @brief Base function object for search predicate in k-search.
    /// returns true when the given k-node is an admissable neighbour
    /// Derive from this class to define your own search predicate and overwrite the operator().
    struct KDNodePredicate
    {
        virtual ~KDNodePredicate() {}
        virtual bool operator()(const KDNode&) const { return true; };
    };

}

#endif