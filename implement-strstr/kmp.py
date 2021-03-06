# leetcode.com boilerplate
class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        return kmp(needle, haystack)


def kmp(pattern, subject):
    if pattern == "":
        return 0

    table = longest_prefix_suffix_table(pattern)
    i = 0 # index into subject
    j = 0 # index into pattern

    while True:
        if j == len(pattern):
            return i - j # found match
        elif i == len(subject):
            break # no match

        if subject[i] == pattern[j]:
            i += 1
            j += 1
        elif j == 0:
            i += 1
        else:
            j = table[j - 1]

    return -1 # no match


def longest_prefix_suffix_table(pattern):
    assert pattern # no empty patterns

    # TODO: How do you describe what `length` is?  As in, what it means.
    length = 0
    table = [0] * len(pattern)

    i = 1
    while i < len(pattern):
        if pattern[i] == pattern[length]:
            length += 1
            table[i] = length
            i += 1
        elif length == 0:
            table[i] = 0
            i += 1
        else:
            length = table[length - 1]

    return table
