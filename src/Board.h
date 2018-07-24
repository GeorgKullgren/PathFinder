#include "Node.h"
#include <vector>


// Class representing the board.
// The board is an array with the height and width specified separately.
// Each node on the board is either:
// 0: Unpassable node
// 1: Passable node
class Board
{
public:
    Board(const unsigned char* pMap, const int nMapWidth, const int nMapHeight);

    // Return vector with nodes reacable form the current node
    std::vector<Node> getReachableNodes(Node node) const;

private:
    // Check if node is passable in map
    bool isPassable(Node node) const;

    const unsigned char* mpMap;
    int mWidth;
    int mHeight;
};

