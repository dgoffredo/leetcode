
from collections import deque
from typing import List


class Solution:
    def ladderLength(self,
                     beginWord: str,
                     endWord: str,
                     wordList: List[str]) -> int:
        return distance(beginWord, endWord, wordList)


def distance(begin, end, words):
    words = set(words)

    if end not in words:
        return 0

    if begin in words:
        words.remove(begin)

    candidates = deque() # (left) to_pop ... to_append (right)
    candidates.append((begin, 1)) # (word, depth)
    while candidates:
        # print(candidates)
        word, when = candidates.popleft()
        if word == end:
            return when

        neighbors = adjacent_words(word, words)
        # print(word, 'has the following neighbors:', neighbors)
        for neighbor in neighbors:
            candidates.append((neighbor, when + 1)) # to possibly examine later
            words.remove(neighbor)                  # to avoid cycles

    return 0 # no path found


# 'a' to 'z', inclusive
alphabet = [chr(code) for code in range(ord('a'), ord('z') + 1)]


def adjacent_words(word, words):
    neighbors = []

    for i, char in enumerate(word):
        for letter in alphabet:
            if letter == char:
                continue
            mutant = word[:i] + letter + word[i+1:]
            if mutant in words:
                neighbors.append(mutant)

    return neighbors
