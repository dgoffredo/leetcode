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

    # Now we can calculate the contribution of each cell to the total capacity.
    capacity = 0
    for j in range(len(heights[0])):
        for i in range(len(heights)):
            height, max_north, max_south, max_east, max_west = heights[i][j]
            rim = min(max_north, max_south, max_east, max_west)
            volume = rim - height
            if volume > 0:
                print(i, j, 'contributes', volume)
                capacity += volume

    return capacity
