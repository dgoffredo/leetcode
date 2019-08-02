from typing import Dict, List, Optional


# leetcode.com boilerplate
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        return word_search(board, words)


class TrieNode:
    match: Optional[str]
    children: Dict[str, 'TrieNode']

    def __init__(self):
        self.match = None
        self.children = {}


def build_backwards_trie(words):
    root = TrieNode()
    node = root
    for word in words:
        for char in reversed(word):
            node = node.children.setdefault(char, TrieNode())

        # The `words` are distinct, so we can assume there's no `match` here.
        assert node.match is None
        node.match = word

        node = root

    return root


def mark(board, i, j):
    board[i][j] = board[i][j].upper()


def is_marked(board, i, j):
    return board[i][j].isupper()


def unmark(board, i, j):
    board[i][j] = board[i][j].lower()


def search_trie(trie, reversed_letters):
    node = trie
    matches = []

    # We ignore the empty string possibility.
    for letter in reversed_letters:
        node = node.children.get(letter)
        if node is None:
            break
        if node.match is not None:
            matches.append(node.match)

    return matches


def word_search(board, words):
    m = len(board)
    n = len(board[0])

    def in_range(i, j):
        return i >= 0 and i < m and j >= 0 and j < n

    def available(i, j):
        return in_range(i, j) and not is_marked(board, i, j)

    trie = build_backwards_trie(words)
    found = set()
    letters = []
    
    def visit(i, j):
        letters.append(board[i][j])

        for match in search_trie(trie, reversed(letters)):
            found.add(match)

        mark(board, i, j)

        for point in [(i + 1, j), (i, j + 1), (i - 1, j), (i, j - 1)]:
            if available(*point):
                visit(*point)

        unmark(board, i, j)
        letters.pop()

    for i in range(m):
        for j in range(n):
            visit(i, j)

    return list(found)

"""
print(Solution().findWords(
    [
        ['o','a','a','n'],
        ['e','t','a','e'],
        ['i','h','k','r'],
        ['i','f','l','v']
    ], 
    ["oath","pea","eat","rain"]))
"""