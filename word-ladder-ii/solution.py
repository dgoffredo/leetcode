from collections import deque
from typing import List


class Solution:
    def findLadders(self,
                    beginWord: str,
                    endWord: str,
                    wordList: List[str]) -> List[List[str]]:
        return [list(ladder) for ladder in ladders(beginWord, endWord, wordList)]


def ladders(begin, end, words):
    # word -> path length when first seen
    words = {word: None for word in words}

    if end not in words:
        return

    if begin in words:
        del words[begin]

    candidates = deque() # (left) to popleft ... to append (right)
    candidates.append((begin,)) # (path...)
    min_path_len = None
    while candidates:
        # print('candidates:', candidates)
        path = candidates.popleft()
        if min_path_len is not None and len(path) > min_path_len:
            break

        *_, word = path
        if word == end:
            min_path_len = len(path)
            yield path

        neighbors = adjacent_words(path, words)
        # print(word, 'has the following neighbors:', neighbors)
        for neighbor in neighbors:
            new_path = (*path, neighbor)
            candidates.append(new_path) # to examine later


# 'a' to 'z', inclusive
alphabet = [chr(code) for code in range(ord('a'), ord('z') + 1)]


def adjacent_words(path, words):
    *_, word = path
    neighbors = []

    for i, char in enumerate(word):
        for letter in alphabet:
            if letter == char:
                continue
            mutant = word[:i] + letter + word[i+1:]
            if mutant in words:
                when = words[mutant]
                if when is not None and when < len(path):
                    continue
                # otherwise, this is a neighbor, and we can note how long the
                # path was when we encountered the word
                neighbors.append(mutant)
                words[mutant] = len(path)

    return neighbors
