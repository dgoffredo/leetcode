# leetcode.com boilerplate
class Solution:
    def longestPalindrome(self, s: str) -> str:
        return longest_palindrome(s)


def longest_palindrome(text):
    longest = ''
    for i in range(len(text)):
        for j in range(i + len(longest) + 1, len(text) + 1):
            substring = text[i:j]
            if is_palindrome(substring):
                longest = substring

    return longest
            

def is_palindrome(text):
    return text[::-1] == text
