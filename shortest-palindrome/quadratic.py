
# leetcode.com boilerplate
class Solution:
    def shortestPalindrome(self, s: str) -> str:
        return shortest_palindromizing_prefix(s) + s


def shortest_palindromizing_prefix(text):
    """Return the shortest (possibly empty) string that can be prepended to the
    specified `text` in order to make the resulting total string a palindrome.
    """
    prefix = ''
    for char in reversed(text):
        if is_palindrome(prefix + text):
            break
        else:
            prefix += char

    return prefix


def is_palindrome(text):
    return reversed_str(text) == text


def reversed_str(text):
    return text[::-1]
