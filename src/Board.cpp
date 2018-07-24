#include "Board.h"

Board::Board(const unsigned char* pMap, const int nMapWidth, const int nMapHeight)
    : mpMap(pMap)
    , mWidth(nMapWidth)
    , mHeight(nMapHeight)
{}

std::vector<Node>  Board::getReachableNodes(Node node) const
{
    std::vector<Node> reachable;

    if (getX(node) > 0)
    {
        Node possible(node);
        getX(possible)--;

        if (isPassable(possible))
        {
            reachable.push_back(possible);
        }
    }
    if (getX(node) < mWidth-1)
    {
        Node possible(node);
        getX(possible)++;

        if (isPassable(possible))
        {
            reachable.push_back(possible);
        }
    }
    if (getY(node) > 0)
    {
        Node possible(node);
        getY(possible)--;

        if (isPassable(possible))
        {
            reachable.push_back(possible);
        }
    }
    if (getY(node) < mHeight-1)
    {
        Node possible(node);
        getY(possible)++;

        if (isPassable(possible))
        {
            reachable.push_back(possible);
        }
    }

    return reachable;
}

bool Board::isPassable(Node node) const
{
    int index = getY(node) * mWidth + getX(node);

    return mpMap[index];
}
