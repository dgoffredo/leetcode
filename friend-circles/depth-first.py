
from typing import List

class Solution:
    def findCircleNum(self, M: List[List[int]]) -> int:
        return num_connected_components(M)


def num_connected_components(adjacency_matrix):
    "TODO"