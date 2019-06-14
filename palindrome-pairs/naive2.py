from itertools import chain


# leetcode.com boilerplate
from typing import List


class Solution:
    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        return palindrome_pairs(words)


def palindrome_pairs(words):
    result = []
    for i in range(len(words)):
        for j in range(len(words)):
            if i != j and concatentation_is_palindrome(words[i], words[j]):
                result.append([i, j])

    return result


def concatentation_is_palindrome(left, right):
    i = chain(left, right)
    j = chain(reversed(right), reversed(left))

    for _ in range((len(left) + len(right)) // 2):
        if next(i) != next(j):
            return False

    return True
