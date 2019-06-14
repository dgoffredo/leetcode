
# leetcode.com boilerplate
class Solution:
    def shortestPalindrome(self, s: str) -> str:
        return shortest_palindromizing_prefix(s) + s


def shortest_palindromizing_prefix(text):
    """Return the shortest (possibly empty) string that can be prepended to the
    specified `text` in order to make the resulting total string a palindrome.

    The strategy is to maintain two stacks of characters. The first,
    `prefix`, are the characters in the answer: the characters to be
    prepended to `text` in order to make it a palindrome. The second stack,
    `backup`, are characters that had a corresponding matching "partner" as
    we proceeded through the characters of the input, but that we might need
    to add to the output later if a non-matching pair is later found.
    """
    prefix = []
    backup = []

    # `i` is an index advancing from the front of `text`, while `j` is an index
    # moving in reverse from the back of `text`.
    i = 0
    j = len(text) - 1
    while i < j:
        if text[i] == text[j]:
            backup.append(text[i])
            i += 1
            j -= 1
            continue

        # We have a mismatch.  First, move any backed up characters into the
        # prefix, and update `i` accordingly.  After that, add the character at
        # `j` to the prefix, and continue, but keep `i` where it is.
        while backup:
            prefix.append(backup.pop())
            i -= 1

        prefix.append(text[j])
        j -= 1

    return ''.join(prefix)