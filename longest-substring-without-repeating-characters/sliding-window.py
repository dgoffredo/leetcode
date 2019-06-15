# leetcode.com boilerplate
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        return len(longest_nonrepeating_substring(s))


from collections import Counter


def highest_count(counter):
    rankings = counter.most_common(1)
    if len(rankings) == 0:
        return 0

    (_, count), *_ = rankings
    return count


def longest_nonrepeating_substring(text):
    longest_i, longest_j = 0, 0
    char_counts = Counter()
    i = 0
    j = 0
    while True:
        if j > len(text):
            break
        elif highest_count(char_counts) <= 1:
            if j - i > longest_j - longest_i:
                longest_i, longest_j = i, j
            j += 1
            if j - 1 < len(text):
                char_counts[text[j - 1]] += 1
        else:
            char_counts[text[i]] -= 1
            i += 1
            assert i <= j # because length one and zero have no duped letters

    return text[longest_i:longest_j]
