from typing import List
from collections import defaultdict

class Solution:
    def numberOfBoomerangs(self, points: List[List[int]]) -> int:
        return count_boomerangs(points)


def distance_squared(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    return (x2 - x1)**2 + (y2 - y1)**2


def count_boomerangs(points):
    total_count = 0
    for p in points:
        print('looking at', p)
        counts = defaultdict(int)
        for other in points:
            print('    comparing', p, 'with', other)
            if other == p:
                continue
            squared_distance = distance_squared(p, other)
            print('    distance from', p, 'to', other, 'is', squared_distance)
            counts[squared_distance] += 1
            print()

        for value, count in counts.items():
            if count > 1:
                total_count += count * 2

    return total_count

def test():
    case = [[0,0],[1,0],[-1,0],[0,1],[0,-1]]
    # TODO
