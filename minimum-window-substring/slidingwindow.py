from collections import defaultdict


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        return shortest_substring_containing_chars(s, t)


def shortest_substring_containing_chars(string, chars):
    if len(string) == 0:
        return ''

    thresholds = defaultdict(int)  # letter in chars -> count in chars
    for ch in chars:
        thresholds[ch] += 1

    counts = defaultdict(int)  # letter in chars -> count in current substring
    num_contained = 0  # how many of `chars` are in the current substring

    shortest = None  # (i, j) of the shortest candidate so far

    i = 0  # index in `string` to the beginning of the current substring
    j = 1  # index in `string` to one-past-the-last of the current substring

    def remove(ch):
        nonlocal num_contained

        threshold = thresholds.get(ch)

        if threshold is None:
            return
   
        counts[ch] -= 1
        if counts[ch] == threshold - 1:
            num_contained -= 1

    def add(ch):
        nonlocal num_contained

        threshold = thresholds.get(ch)

        if threshold is None:
            return

        counts[ch] += 1
        if counts[ch] == threshold:
            num_contained += 1
        
    add(string[0])

    while True:
        if num_contained == len(thresholds):
            # Maybe found a new candidate.
            if shortest is None or j - i < shortest[1] - shortest[0]:
                shortest = i, j

            # If we can shrink from the left, then do so, since then we might
            # have found a shorter substring that still has all the chars.
            if i == j - 1:
                if j == len(string):
                    break  # can't move right any more
 
                remove(string[i])
                add(string[j])

                i += 1
                j += 1
            else:
                remove(string[i])
                i += 1
        else:
            # We have yet to cover all of the chars.  Expand to the right if
            # possible.
            if j == len(string):
                break  # can't expand any more, and there's no use in shrinking

            add(string[j])
            j += 1

    if shortest is None:
        return ''
    else:
        i, j = shortest
        return string[i:j]
