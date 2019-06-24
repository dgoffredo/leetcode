from collections import deque
from typing import List

class Solution:
    def findLadders(self,
                    beginWord: str,
                    endWord: str,
                    wordList: List[str]) -> List[List[str]]:
        return [list(ladder) for ladder in ladders(beginWord, endWord, wordList)]


def ladders(begin, end, words):
    words = set(words)

    if end not in words:
        return

    if begin in words:
        words.remove(begin)

    candidates = deque() # (left) to popleft ... to append (right)
    candidates.append(((begin,), set([begin]))) # (path..., set(path...))
    min_path_len = None
    while candidates:
        # print('candidates:', candidates)
        path, path_set = candidates.popleft()
        if min_path_len is not None and len(path) > min_path_len:
            break

        *_, word = path
        if word == end:
            min_path_len = len(path)
            yield path

        neighbors = adjacent_words(word, words - path_set)
        # print(word, 'has the following neighbors:', neighbors)
        for neighbor in neighbors:
            new_path = (*path, neighbor)
            candidates.append((new_path, set(new_path))) # to examine later


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
