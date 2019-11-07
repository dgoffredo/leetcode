from collections import defaultdict


class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        return contains_permutation(subject=s2, pattern=s1)


def contains_permutation(subject, pattern):
    if len(subject) < len(pattern):
        return False

    thresholds = defaultdict(int)  # char in `pattern` -> how many times
    for ch in pattern:
        thresholds[ch] += 1

    counts = defaultdict(int)  # char from `pattern` in current slice -> count
    num_matching = 0  # how many unique chars in current slice are satisfied

    def add(ch):
        nonlocal num_matching

        threshold = thresholds.get(ch)
        if threshold is None:
            return

        counts[ch] += 1
        if counts[ch] == threshold:
            num_matching += 1

    def remove(ch):
        nonlocal num_matching

        threshold = thresholds.get(ch)
        if threshold is None:
            return

        counts[ch] -= 1
        if counts[ch] == threshold - 1:
            num_matching -= 1


    for i in range(len(pattern)):
        add(subject[i])

    if num_matching == len(thresholds):
        return True

    for j in range(len(pattern), len(subject)):
        i = j - len(pattern)

        # (i, j) is where we just were, so we remove the i'th and add the j'th
        remove(subject[i])
        add(subject[j])

        if num_matching == len(thresholds):
            return True

    return False
