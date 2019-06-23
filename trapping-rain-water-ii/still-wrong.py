from typing import List


# leetcode.com boilerplate
class Solution:
    def trapRainWater(self, heightMap: List[List[int]]) -> int:
        return water_capacity(heightMap)


def water_capacity(heights):
    # Need to find the maximum height to the north, south, east, and west of
    # each point. North and west can be determined by a forward traversal,
    # while south and east can be determined by a backward traversal. We can
    # store all relevant information in the input matrix, to save space. The
    # input has a single integer, the height, in each cell. We'll overwrite
    # that with a tuple (height, max_north, max_south, max_east, max_west).

    if len(heights) == 0 or len(heights[0]) == 0:
        return 0

    def get(i, j):
        if i >= 0 and j >= 0 and i < len(heights) and j < len(heights[0]):
            return heights[i][j]
        else:
            return (0, 0, 0, 0, 0)

    # forward traversal to determine "max to the north" and "max to the west".
    for j in range(len(heights[0])):
        for i in range(len(heights)):
            height = heights[i][j]
            north, max_north, *_ = get(i - 1, j)
            max_north = max(north, max_north)
            west, _, _, _, max_west = get(i, j - 1)
            max_west = max(west, max_west)
            heights[i][j] = height, max_north, 0, 0, max_west

    # backward traversal to determine "max to the south" and "max to the east".
    for j in range(len(heights[0])):
        j = len(heights[0]) - j - 1
        for i in range(len(heights)):
            i = len(heights) - i - 1
            height, max_north, _, _, max_west = heights[i][j]
            south, _, max_south, *_ = get(i + 1, j)
            max_south = max(south, max_south)
            east, _, _, max_east, _ = get(i, j + 1)
            max_east = max(east, max_east)
            heights[i][j] = height, max_north, max_south, max_east, max_west

    # We're not quite done yet. Were we to calculate the volume contribution of
    # each cell based only on the information so far obtained, we could get the
    # wrong answer due to water's availability to flow in directions other than
    # just along the axes. We wish to find the minimum height of the "rim" of
    # each "pool," but in order to do this we need to find the connected
    # components of the "cells that contribute anything at all" graph.
    # So, we find the connected components (pools), and for each note the
    # minimum rim height, so that then we can go back and calculate the correct
    # volume contribution of each well within each pool.
    pool_index = {} # {(i, j): index}
    pool_min_rim = []
    current_pool = -1
    for j in range(len(heights[0])):
        for i in range(len(heights)):
            if (i, j) in pool_index:
                continue

            height, max_north, max_south, max_east, max_west = get(i, j)
            rim = min(max_north, max_south, max_east, max_west)
            volume = rim - height
            if volume <= 0:
                continue

            current_pool += 1
            pool_min_rim.append(rim)
            def explore_pool(i, j):
                if (i, j) in pool_index:
                    return

                height, max_north, max_south, max_east, max_west = get(i, j)
                rim = min(max_north, max_south, max_east, max_west)
                volume = rim - height
                if volume <= 0:
                    return

                pool_index[i, j] = current_pool
                pool_min_rim[current_pool] = min(rim, pool_min_rim[current_pool])

                # here's the exploring part
                for a, b in [(i - 1, j), (i, j - 1), (i + 1, j), (i, j + 1)]:
                    explore_pool(a, b)

            explore_pool(i, j)

    # We've now populated rim height information, so we can accumulate the
    # total trapped capacity of water.
    print(pool_index)
    print(pool_min_rim)
    capacity = 0
    for (i, j), pool in pool_index.items():
        height, *_ = heights[i][j]
        rim = pool_min_rim[pool]
        volume = rim - height
        if volume > 0:
            capacity += volume

    return capacity

                
