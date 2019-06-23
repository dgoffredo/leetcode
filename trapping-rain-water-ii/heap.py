from typing import List


# leetcode.com boilerplate
class Solution:
    def trapRainWater(self, heightMap: List[List[int]]) -> int:
        return water_capacity(heightMap)


# This solution is copied from an animation found in the "discussion" section.
import heapq

def water_capacity(heights):
    if len(heights) <= 2 or len(heights[0]) <= 2:
        return 0

    heap = []
    def push(height, i, j):
        heapq.heappush(heap, (height, i, j))

    def pop():
        return heapq.heappop(heap)

    # The edges never hold any water, so first push them onto the heap. Any
    # cell (i, j) that we've visited is overwritten with None.

    # first and last row
    for i in [0, len(heights) - 1]:
        for j in range(len(heights[0])):
            push(heights[i][j], i, j)
            heights[i][j] = None # mark visited

    # first and last column, excluding the first and last row
    for j in [0, len(heights[0]) - 1]:
        for i in range(1, len(heights) - 1):
            push(heights[i][j], i, j)
            heights[i][j] = None # mark visited

    max_height = -1
    capacity = 0
    # While we have points to examine, pop them off of the heap. For each,
    # possibly update `max_height` (if the height is larger than it), and then
    # visit each of its neighbors. If a neighbor hasn't been visited before,
    # then push it onto the heap, and also possibly contribute to the total
    # volume of water if its height is less than the `max_height` at that time.
    while heap:
        height, i, j = pop()
        if height > max_height:
            max_height = height
        for di, dj in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
            a, b = i + di, j + dj
            if a >= 0 and b >= 0 and a < len(heights) and b < len(heights[0]):
                neighbor = heights[a][b]
                if neighbor is not None:
                    push(neighbor, a, b)
                    if neighbor < max_height:
                        capacity += max_height - neighbor
                    heights[a][b] = None # mark visited

    return capacity
