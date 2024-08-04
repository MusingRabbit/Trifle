#ifndef GTEST_HELPER
#define GTEST_HELPER

#include <iostream>
#include <string>

#include <trifle.h>

#define ANSI_TXT_GRN "\033[0;32m"
#define ANSI_TXT_MGT "\033[0;35m" // Magenta
#define ANSI_TXT_DFT "\033[0m"  // Console default
#define GTEST_BOX "[     cout ] "
#define COUT_GTEST ANSI_TXT_GRN << GTEST_BOX // You could add the Default
#define COUT_GTEST_MGT COUT_GTEST << ANSI_TXT_MGT

using namespace tfl;

class GTestHelper
{
  public:
    static void ConsoleWrite(std::string msg)
    {
        std::cout << COUT_GTEST_MGT << msg.c_str() << ANSI_TXT_DFT << std::endl;
    }

    static std::shared_ptr<tfl::EntityManager> CreateEntityManager()
    {
        std::shared_ptr<tfl::EntityManager> entityManager = std::make_shared<tfl::EntityManager>();
        entityManager->Init();

        entityManager->RegisterComponent<Transform>();
        entityManager->RegisterComponent<Collider>();
        entityManager->RegisterComponent<Model3D>();
        entityManager->RegisterComponent<Movement>();
        entityManager->RegisterComponent<Projection>();
        entityManager->RegisterComponent<Target>();

        return entityManager;
    }
};

class KDTreeTestHelper
{
    public:
    static KDTree CreateTree(int distanceType = 2)
    {
        std::vector<KDNode> nodes;

        nodes.push_back(KDNode({1, 1}));
        nodes.push_back(KDNode({2, 1}));
        nodes.push_back(KDNode({1, 2}));
        nodes.push_back(KDNode({2, 4}));
        nodes.push_back(KDNode({3, 4}));
        nodes.push_back(KDNode({7, 2}));
        nodes.push_back(KDNode({8, 3}));
        nodes.push_back(KDNode({8, 5}));
        nodes.push_back(KDNode({7, 3}));
        nodes.push_back(KDNode({7, 3}));

        KDTree tree;
        tree.Init(nodes, distanceType);
        return tree;
    }
};

#endif // !GTEST_HELPER