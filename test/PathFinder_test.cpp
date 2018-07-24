#include "gtest/gtest.h"
#include "PathFinder.h"


/**
 * Test with 0 size map
 **/
TEST(PathFinder_tests, test_no_map)
{
    unsigned char pMap[] = {};
    int pOutBuffer[7];
    ASSERT_DEATH(FindPath(0, 1, 2, 3, pMap, 0, 0, pOutBuffer, 7),
                 ".*Assertion `nMapWidth > 0 && nMapHeight > 0' failed.");
}

/**
 * Test target outside map
 **/
TEST(PathFinder_tests, test_target_outside_map)
{
    unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int pOutBuffer[12];

    ASSERT_DEATH(FindPath(0, 0, 4, 2, pMap, 4, 3, pOutBuffer, 12),
                 ".*Assertion `nTargetX < nMapWidth && nTargetY < nMapHeight' failed.");
}

/**
 * Test start outside map
 **/
TEST(PathFinder_tests, test_start_outside_map)
{
    unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int pOutBuffer[12];

    ASSERT_DEATH(FindPath(7, 0, 2, 2, pMap, 4, 3, pOutBuffer, 12),
                 ".*Assertion `nStartX < nMapWidth && nStartY < nMapHeight' failed.");
}

/**
 * Test with map containing only one node
 **/
TEST(PathFinder_tests, test_same_node_for_start_and_target)
{
    unsigned char pMap[] = {1};
    int pOutBuffer[7];
    int pathLength = FindPath(0, 0, 0, 0, pMap, 1, 1, pOutBuffer, 7);

    EXPECT_EQ(0, pathLength);
}

/**
 * Verify that the correct path is found
 **/
TEST(PathFinder_tests, test_length_3)
{
  unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
  int pOutBuffer[12];

  int expectedPathLength = 3;
  int expectedPath[] = {1, 5, 9};

  int pathLength = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

  EXPECT_EQ(expectedPathLength, pathLength);

  for (int i = 0; i < expectedPathLength; i++)
    {
      EXPECT_EQ(expectedPath[i], pOutBuffer[i]);
    }
}

/**
 * Verify that -1 is returned if no path is found
 **/
TEST(PathFinder_tests, test_no_path_found)
{
  unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
  int pOutBuffer[7];
  int pathLength = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);

  EXPECT_EQ(-1, pathLength);
}

/**
 * Verify that the length of the path is returned and the provided buffer
 * does not overflow if it is too small
 **/
TEST(PathFinder_tests, test_too_small_buffer)
{
    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    int pOutBuffer[3];
    int pOutBufferLength = 2;

    int expectedPathLength = 3;
    int expectedPath[] = {1, 5, 9};


    pOutBuffer[pOutBufferLength] = 999;

    int pathLength = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, pOutBufferLength);

    EXPECT_EQ(expectedPathLength, pathLength);

    for (int i = 0; i < pOutBufferLength; i++)
    {
        EXPECT_EQ(expectedPath[i], pOutBuffer[i]);
    }

    // The last step didn't fit in the buffer. Verify that the value is unchanged.
    EXPECT_EQ(999, pOutBuffer[pOutBufferLength]);
}


/**
 * Verify that the path can be found in a map with only a single row
 **/
TEST(PathFinder_tests, test_single_row_map)
{
  unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int pOutBuffer[12];

  int expectedPathLength = 6;
  int expectedPath[] = {1, 2, 3, 4, 5, 6};

  int pathLength = FindPath(0, 0, 6, 0, pMap, 12, 1, pOutBuffer, 12);

  EXPECT_EQ(expectedPathLength, pathLength);

  for (int i = 0; i < expectedPathLength; i++)
    {
      EXPECT_EQ(expectedPath[i], pOutBuffer[i]);
    }
}

/**
 * Verify that the path can be found in a map with only a single column
 **/
TEST(PathFinder_tests, test_single_column_map)
{
  unsigned char pMap[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int pOutBuffer[12];

  int expectedPathLength = 6;
  int expectedPath[] = {3, 4, 5, 6, 7, 8};

  int pathLength = FindPath(0, 2, 0, 8, pMap, 1, 12, pOutBuffer, 12);

  EXPECT_EQ(expectedPathLength, pathLength);

  for (int i = 0; i < expectedPathLength; i++)
    {
      EXPECT_EQ(expectedPath[i], pOutBuffer[i]);
    }
}


/**
 * Test with a large map.
 **/
TEST(PathFinder_tests, test_large_map)
{
  unsigned char pMap[] = {1, 1, 0, 1, 1, 1, 0, 1, 1, 1,
                          1, 1, 0, 1, 0, 1, 0, 0, 0, 1,
                          1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
                          1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                          0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
                          1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
                          1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
                          1, 1, 1, 1, 1, 0, 1, 1, 0, 1,
                          1, 1, 1, 1, 1, 0, 1, 1, 0, 1,
                          1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int pOutBuffer[50];

  int expectedPathLength = 46;

  // Several paths are valid. Parts that are unkown are listed with '-1'
  int expectedPath[] = {11, 21, 31, 32, 33, 23, 13, 3, 4, 5, 15, 25, 35, 45, 55,
                        54, 53, 52, 51, 50, 60, 70, -1, -1, -1, -1, -1, -1, -1,
                        105, -1, -1, -1, -1, 99, 89, 79, 69, 59, 49, 39, 29, 19,
                        9, 8, 7};

  int pathLength = FindPath(1, 0, 7, 0, pMap, 10, 11, pOutBuffer, 50);

  EXPECT_EQ(expectedPathLength, pathLength);

  for (int i = 0; i < expectedPathLength; i++)
    {
      // Only validate mandatory parts of the path
      if (expectedPath[i] != -1)
        {
          EXPECT_EQ(expectedPath[i], pOutBuffer[i]);
        }
    }
}
