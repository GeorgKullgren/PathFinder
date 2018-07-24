#include "Board.h"
#include "Node.h"
#include "PathFinder.h"

#include <cassert>
#include <algorithm>
#include <climits>
#include <list>
#include <queue>
#include <vector>

int& getDistance(std::vector<std::vector<int> >& dist, Node& node)
{
    return dist[getX(node)][getY(node)];
}

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY, 
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize)
{
    assert(pOutBuffer != NULL);
    assert(pOutBuffer != nullptr);
    assert(nMapWidth > 0 && nMapHeight > 0);
    assert(nStartX < nMapWidth && nStartY < nMapHeight);
    assert(nTargetX < nMapWidth && nTargetY < nMapHeight);

    Board board(pMap, nMapWidth, nMapHeight);
    Node start(nStartX, nStartY);
    Node target(nTargetX, nTargetY);

    // Nodes that have been reached but pending next step
    std::queue<Node> pending;

    // Distance from start position. Initialized to INT_MAX
    std::vector<std::vector<int> > dist(nMapWidth, std::vector<int>(nMapHeight, INT_MAX));

    pending.push(start);
    getDistance(dist, start) = 0;

    // Use Dijkstra to create a distance map
    while (!pending.empty())
    {
        Node node = pending.front();
        pending.pop();
        if (node == target)
        {
            break;
        }

        for (auto next: board.getReachableNodes(node))
        {
            if (getDistance(dist, node) + 1 < getDistance(dist, next))
            {
                getDistance(dist, next) = getDistance(dist, node) + 1;
                pending.push(next);
            }
        }

    }


    // Trace back the shortest path
    if (getDistance(dist, target) != INT_MAX)
    {
        std::list<Node> path;
        Node node(target);
        path.push_front(node);

        // Create a list of nodes representing the path between start and target
        while ((node = path.front()) != start)
        {
            // Get the neighbour nodes and find the neighbour with the lowest distance value
            std::vector<Node> neighbours = board.getReachableNodes(node);
            std::nth_element(neighbours.begin(), neighbours.begin(), neighbours.end(),
                             [&dist](Node& l, Node& r)
                             {
                                 return getDistance(dist, l) < getDistance(dist, r);
                             });
            path.push_front(neighbours.front());
        }
        path.pop_front(); // Drop start position

        // Put the map indexes for the path in pOutBuffer
        int pathLength = path.size();
        for (int i = 0; i < std::min(pathLength, nOutBufferSize) ; i++)
        {
            Node n = path.front();
            path.pop_front();
            pOutBuffer[i] = n.second * nMapWidth + n.first;
        }
        return pathLength;
    }

    return -1;
}
