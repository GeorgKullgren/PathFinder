
/**
 * Find shortest path between two positions in a map
 *
 * Input:
 * nStartX, nStartY   - x and y coordinates for start position
 * nTargetX, nTargetY - x and y coordinates for target position
 * pMap               - The map to be traversed
 *                      values 1/0 for passable/unpassable positions
 * nMapWidth, nMapHeight - Width and height oh map
 * pOutBuffer         - Buffer containing the shortest path.
 *                      Content is undefined if no path is found
 * nOutBufferSize     - Size of buffer
 *
 * Returns:
 * Length of shortest path or -1 if no path is found
 **/
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY, 
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);
