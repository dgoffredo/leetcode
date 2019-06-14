# leetcode.com boilerplate
class Solution:
    def longestPalindrome(self, s: str) -> str:
        return longest_palindrome(s)


def longest_palindrome(text):
    longest = ''
    i, j = 0, 1

    # Advance "inchworm style," with the lower index `i` always strictly less
    # than the one-past-the-last upper index `j`.
    while True:
        if j > len(text):
            break
        elif j - i <= len(longest):
            j += 1
        elif is_palindrome(text[i:j]):
            longest = text[i:j]
            j += 1
        else:
            i += 1
        
    return longest


def is_palindrome(text):
    return text[::-1] == text
