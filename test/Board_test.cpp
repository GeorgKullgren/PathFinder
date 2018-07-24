#include "gtest/gtest.h"
#include "Board.h"

#include <set>

/**
 * Test with all for directions being reachable
 **/
TEST(Board_tests, find_four_nodes)
{
    unsigned char pMap[] = {1, 1, 1,
                            1, 1, 1,
                            1, 1, 1};

    Board board(pMap, 3, 3);
    Node startPosition(1, 1);
    std::set<Node> expectedNodes = {Node(0, 1), Node(1, 0), Node(1, 2), Node(2, 1)};

    std::vector<Node> reachableNodes = board.getReachableNodes(startPosition);

    EXPECT_EQ(expectedNodes.size(), reachableNodes.size());
    for (Node node : reachableNodes)
    {
        int erasedNode = expectedNodes.erase(node);
        EXPECT_EQ(1, erasedNode);
    }
    EXPECT_EQ(0, expectedNodes.size());
}

/**
 * Test with no reachable nodes
 **/
TEST(Board_tests, no_reachable_nodes)
{
    unsigned char pMap[] = {0, 0, 0,
                            0, 1, 0,
                            0, 0, 0};

    Board board(pMap, 3, 3);
    Node startPosition(1, 1);
    std::set<Node> expectedNodes = {};

    std::vector<Node> reachableNodes = board.getReachableNodes(startPosition);

    EXPECT_EQ(expectedNodes.size(), reachableNodes.size());
    for (Node node : reachableNodes)
    {
        int erasedNode = expectedNodes.erase(node);
        EXPECT_EQ(1, erasedNode);
    }
    EXPECT_EQ(0, expectedNodes.size());
}

/**
 * Search reachables nodes from corner. Only 2 should be found
 **/
TEST(Board_tests, search_from_corner)
{
    unsigned char pMap[] = {1, 1, 1,
                            1, 1, 1,
                            1, 1, 1};

    Board board(pMap, 3, 3);
    Node startPosition(2, 0);
    std::set<Node> expectedNodes = {Node(1, 0), Node(2, 1)};

    std::vector<Node> reachableNodes = board.getReachableNodes(startPosition);

    EXPECT_EQ(expectedNodes.size(), reachableNodes.size());
    for (Node node : reachableNodes)
    {
        int erasedNode = expectedNodes.erase(node);
        EXPECT_EQ(1, erasedNode);
    }
    EXPECT_EQ(0, expectedNodes.size());
}

