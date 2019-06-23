
from typing import List


class Solution:
    def ladderLength(self,
                     beginWord: str,
                     endWord: str,
                     wordList: List[str]) -> int:
        return distance(beginWord, endWord, wordList)


def differ_by_one(left, right):
    return sum(a == b for a, b in zip(left, right)) == len(left) - 1


def neighbors_graph(words):
    # graph :: word -> set(adjacent words...)
    graph = {word: set() for word in words}

    for word in words:
        for other in words - set(word):
            for i in range(len(word)):
                if differ_by_one(word, other):
                    graph[word].add(other)
                    graph[other].add(word)

    return graph


def distance(begin, end, words):
    """The plan is to build a graph of which words in `words + [begin]` are
    connected to which other words. Then a breadth first search through the
    graph starting at `begin` will either find `end`, and thus the answer is
    the current depth, or will not find `end`, meaning that there is no
    path, and so the answer is zero.
    """
    words = set(words)
    words.add(begin)

    if end not in words:
        return 0

    graph = neighbors_graph(words)
 
    nodes = [begin]
    visited = set()
    depth = 1
    while nodes:
        for node in nodes:
            visited.add(node)

        kids = set().union(*(graph[node] for node in nodes)) - visited
        if not kids:
            return 0

        depth += 1

        if end in kids:
            return depth

        nodes = kids

    return depth
    