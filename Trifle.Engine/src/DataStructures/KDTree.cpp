#include "KDTree.h"

#include <stdexcept>


namespace tfl
{
    KDTree::KDTree(const std::vector<KDNode>& nodes, int distanceType)
    {
        size_t i,j; 
        double val;

        m_dimension = nodes.begin()->pos.size();         // Set the dimension to the number of points a vector has. 2D, 3D, 4D etc...
        m_allNodes = nodes;

        // Initialise instance values
        m_distance = nullptr;
        m_distanceType = distanceType;

        SetDistance(m_distanceType, {});
        m_loBound = m_allNodes.begin()->pos;              // Initialise the hi and low bound to the first nodes' point / position.
        m_hiBound = m_allNodes.begin()->pos;

        for (i = 1; i < m_allNodes.size(); i++)             // For every node
        {
            for (j = 0; j < m_dimension; j ++)              // For every dimension
            {
                val = m_allNodes[i].pos[j];               // Set 'val' to that of the point of the current node at the current dimension.
                m_loBound[j] = (m_loBound[j] > val) ? val : m_loBound[j];   // If the low bound is greater than 'val' - set the lowbound to val
                m_hiBound[j] = (m_hiBound[j] < val) ? val : m_hiBound[j];   // If the hi bound is less than 'val' - set the hibound to val.
            }
        }

        m_root = BuildTree(0, 0, m_allNodes.size());
    }

    KDTree::KDTree(const KDTree& rhs)
    {
        m_loBound = rhs.m_loBound;
        m_hiBound = rhs.m_hiBound;
        m_distanceType = rhs.m_distanceType;
        m_distance = rhs.m_distance;
        m_dimension = rhs.m_dimension;
        m_searchPredicate = rhs.m_searchPredicate;
        m_allNodes = std::move(rhs.m_allNodes);
        m_root = rhs.m_root;
    }

    KDTree::~KDTree()
    {
        delete m_root;

        if (m_distance != nullptr)
        {
            delete m_distance;
        }
    }

    void KDTree::SetDistance(int distanceType, const std::vector<double>& weights)
    {
        if (m_distance)
            delete m_distance;

        m_distanceType = distanceType;

        switch (m_distanceType)
        {
        case 0:
            m_distance = (DistanceMeasure*)new DistanceL0(weights);
            break;
        case 1:
            m_distance = (DistanceMeasure*)new DistanceL1(weights);
        break;
        default:
            m_distance = (DistanceMeasure*)new DistanceL2(weights);
            break;
        }
    }

    std::vector<KDNode> KDTree::KNearestNeighbours(const CoordPos& pos, size_t k, KDNodePredicate* predicate)
    {
        KDNode tmp;
        std::vector<KDNode> result;
        m_searchPredicate = predicate;
        SearchQueue neighbourHeap;

        if (k < 1)
        {
            return result;
        }

        if (pos.size() != m_dimension)
        {
            throw std::invalid_argument("KDTree::KNearestNeighbours() : pos must be of same dimension as \"KDTree\"");
        }

        if (k > m_allNodes.size())
        {
            k = m_allNodes.size();

            for (size_t i = 0; i < k; i++)
            {
                if (!(m_searchPredicate && !(*m_searchPredicate)(m_allNodes[i])))
                {
                    neighbourHeap.push(NN4Heap(i, m_distance->Distance(m_allNodes[i].pos, pos)));
                }
            }
        }
        else 
        {
            NeighbourSearch(pos, m_root, k , &neighbourHeap);
        }


        while (!neighbourHeap.empty())
        {
            size_t i = neighbourHeap.top().dataIndex;
            neighbourHeap.pop();
            result.push_back(m_allNodes[i]);
        }

        k = result.size();

        for (size_t i = 0; i < k / 2; i++)
        {
            tmp = result[i];
            result[i] = result[k - 1 - i];
            result[k - 1 - i] = tmp;
        }

        return result;
    }

    std::vector<KDNode> KDTree::RangeNearestNeighbours(const CoordPos& pos, double r)
    {
        std::vector<KDNode> result;
        std::vector<size_t> rangeResult;

        if (pos.size() != m_dimension)
        {
            throw std::invalid_argument("KDTree::KNearestNeighbours() : pos must be of same dimension as \"KDTree\"");
        }

        if (m_distanceType == 2)                                    // if euclidien distance is used the range must be squared because we
        {
            r *= r;                                                 // get squared distances from this implementation
        }

        RangeSearch(pos, m_root, r, &rangeResult);

        for (unsigned int i = 0; i < rangeResult.size(); i++)
        {
            result.push_back(m_allNodes[rangeResult[i]]);
        }

        return result;
    }

    std::vector<KDNode> KDTree::GetAllNodes()
    {
        return m_allNodes;
    }

    KDTreeNode* KDTree::BuildTree(size_t depth, size_t a, size_t b)
    {
        size_t m;
        double temp, cutval;

        KDTreeNode* node = new KDTreeNode();                            // Result tree node
        node->lobound = m_loBound;                                      // Initialise low and hi bound to that of the tree's max and min values
        node->hiBound = m_hiBound;
        node->cutdim = depth % m_dimension;                             // Set nodes cut dimension. This node will deal with the first, second, third...K dimension depending on the current depth of the tree. 

        if (b - a <= 1)                                                 // If b is less than or equal to a. Why is it done this way? Is it more optimal?
        {
            node->dataindex = a;                                        // Set the nodes data index to a
            node->pos = m_allNodes[a].pos;                          // Set the nodes point / position to that of the node at index a
        }
        else 
        {
            m = (a + b) / 2;                                            // Set m to be the midpoint between a and b
            KDNode& midNode = *(&m_allNodes[m]);

            std::nth_element(m_allNodes.begin() + a, m_allNodes.begin() + m, m_allNodes.begin() + b, CompareDimension(node->cutdim));      // Sort the allNodes array for the given comparator.
            node->pos = midNode.pos;                                // Update the current node with the midpoint node details
            cutval = midNode.pos[node->cutdim];
            node->dataindex = m;
                                                                        // Build tree from left to right...
            if (m - a > 0)                                              // If the midpoint is greater than a 
            {
                temp = m_hiBound[node->cutdim];                         // Build the tree for the low child of this node.
                m_hiBound[node->cutdim] = cutval;                       
                node->childLo = BuildTree(depth + 1, a, m);
                m_hiBound[node->cutdim] = temp;
            }
            if (b - m > 1)                                         // ELSE If b is greater than the midpoint
            {
                temp = m_loBound[node->cutdim];                         // Build the tree for the high child of this node.
                m_loBound[node->cutdim] = cutval;
                node->childHi = BuildTree(depth + 1, m + 1, b);
                m_loBound[node->cutdim] = temp;
            }
        }

        return node;                                                     // return the completed node...
    }

    bool KDTree::NeighbourSearch(const CoordPos& pos, KDTreeNode* node, size_t k, SearchQueue* neighbourHeap)
    {
        double currDist, dist;
        double v =  pos[node->cutdim];
        double nV = node->GetValue();
        bool vLessThanNodeV = v < nV;

        currDist = m_distance->Distance(pos, node->pos);

        if (!(m_searchPredicate && !(*m_searchPredicate)(m_allNodes[node->dataindex])))
        {
            if (neighbourHeap->size() < k)
            {
                neighbourHeap->push(NN4Heap(node->dataindex, currDist));
            }
            else if (currDist < neighbourHeap->top().distance)
            {
                neighbourHeap->pop();
                neighbourHeap->push(NN4Heap(node->dataindex, currDist));
            }
        }

        // first search on side closer to point
        if (vLessThanNodeV)
        {
            if (node->childLo)
            {
                if (NeighbourSearch(pos, node->childLo, k, neighbourHeap))
                {
                    return true;
                };
            }
        }
        else 
        {
            if (node->childHi)
            {
                if (NeighbourSearch(pos, node->childHi, k, neighbourHeap))
                {
                    return true;
                };
            }
        }

                
        // second search on farther side, if necessary
        if (neighbourHeap->size() < k)
        {
            dist = std::numeric_limits<double>::max();
        }
        else 
        {
            dist = neighbourHeap->top().distance;
        }
        
        if (vLessThanNodeV)
        {
            if (node->childHi && BoundsOverlapBall(pos, dist, node->childHi))
            {
                if (NeighbourSearch(pos, node->childHi, k, neighbourHeap))
                {
                    return true;
                }
            }
        }
        else if (node->childLo && BoundsOverlapBall(pos, dist, node->childLo))
        {
            if (NeighbourSearch(pos, node->childLo, k, neighbourHeap))
            {
                return true;
            }
        }

        if (neighbourHeap->size() == k)
        {
            dist = neighbourHeap->top().distance;
        }

        return BallWithinBounds(pos, dist, node);
    }

    void KDTree::RangeSearch(const CoordPos& pos, KDTreeNode* node, double r, std::vector<size_t>* rangeResult)
    {
        double currDist = m_distance->Distance(pos, node->pos);

        if (currDist <= r)
        {
            rangeResult->push_back(node->dataindex);
        }

        if (node->childLo != nullptr && BoundsOverlapBall(pos, r, node->childLo))
        {
            RangeSearch(pos, node->childLo, r, rangeResult);
        }

        if (node->childHi != nullptr && BoundsOverlapBall(pos, r, node->childHi))
        {
            RangeSearch(pos, node->childHi, r, rangeResult);
        }
    }

    bool KDTree::BoundsOverlapBall(const CoordPos& pos, double dist, KDTreeNode* node)
    {
        size_t i;

        if (m_distanceType != 0)
        {
            double distSum = 0.0;
            for (i = 0; i < m_dimension; i++)
            {
                if (pos[i] < node->lobound[i])
                {
                    distSum += m_distance->CoordinateDistance(pos[i], node->lobound[i], i);
                }
                else if (pos[i] > node->hiBound[i])
                {
                    distSum += m_distance->CoordinateDistance(pos[i], node->hiBound[i], i);
                }

                if (distSum > dist)
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            double currDist = 0.0;
            double maxDist = 0.0;

            for (i = 0;  i < m_dimension; i ++)
            {
                if (pos[i] < node->lobound[i])
                {
                    currDist = m_distance->CoordinateDistance(pos[i], node->lobound[i], i);
                }
                else if (pos[i] > node->hiBound[i])
                {
                    currDist = m_distance->CoordinateDistance(pos[i], node->hiBound[i], i);
                }

                if (currDist > maxDist)
                {
                    maxDist = currDist;
                }

                if (maxDist > currDist)
                {
                    return false;
                }
            }

            return true;
        }

        return false;
    }

    bool KDTree::BallWithinBounds(const CoordPos& pos, double dist, KDTreeNode* node)
    {
        for (unsigned int i = 0; i < m_dimension; i ++)
        {
            double loDist = m_distance->CoordinateDistance(pos[i], node->lobound[i], i);
            double hiDist = m_distance->CoordinateDistance(pos[i], node->hiBound[i], i);

            if (loDist <= dist || hiDist <= dist)
            {
                return false;
            }
        }
        return true;
    }

} // namespace tfl