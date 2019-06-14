# leetcode.com boilerplate
from typing import List


class Solution:
    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        return palindrome_pairs(words)


def palindrome_pairs(words):
    result = []
    for i in range(len(words)):
        for j in range(len(words)):
            if i != j and is_palindrome(words[i] + words[j]):
                result.append([i, j])

    return result


def is_palindrome(text):
    return reversed_str(text) == text


def reversed_str(text):
    return text[::-1]
