# leetcode.com boilerplate
from typing import List


class Solution:
    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        return palindrome_pairs(words)


def palindrome_pairs(words):
    result = []
    trie = make_trie(words)

    for j, word in enumerate(words):
        subtrie = trie
        candidates = []
        for char in reversed(word):
            # If we've reached the end of any strings, they are candidates.
            ended = subtrie.get('')
            if ended is not None:
                candidates.append(ended)

            subtrie = subtrie.get(char, None)
            # If there are no more other string, we're done.
            if subtrie is None:
                break

        # If we didn't run out of other strings, but instead ran out of
        # characters in our string, then the remaining strings are candidates.
        if subtrie is not None:
            candidates.extend(dredge(subtrie))

        # See which of the candidate prefixes yield palindromes.
        for i in candidates:
            if i == j:
                continue
            if is_palindrome(words[i] + word):
                result.append([i, j])

    return result


def is_palindrome(text):
    return text[::-1] == text


def dredge(trie):
    """Return a list of the leaves of the specified `trie`."""
    leaves = []

    def recurse(subtrie):
        for key, value in subtrie.items():
            if key == '':
                leaves.append(value)
            else:
                recurse(value)

    recurse(trie)
    return leaves


def make_trie(strings):
    trie = {}

    for i, string in enumerate(strings):
        subtrie = trie
        for char in string:
            subtrie = subtrie.setdefault(char, dict())
        subtrie[''] = i

    return trie