# leetcode.com boilerplate
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        return match(p, s)


def match(pattern, subject):
    tokens = pattern

    table = [None] * ((len(tokens) + 1) * (len(subject) + 1))
    
    def get(p, s):
        return table[p * (len(subject) + 1) + s]

    def set(p, s, value):
        table[p * (len(subject) + 1) + s] = value

    for s in range(len(subject), -1, -1):
        for p in range(len(tokens), -1, -1):
            # print('examining', p, 'in pattern and', s, 'in subject.')
            set(p, s, match_suffix(p, tokens, s, subject, get))
            # print('result was', get(p, s))

    return get(0, 0)


def match_suffix(p, pattern, s, subject, recur):
    if p == len(pattern):
        return s == len(subject)
    if s == len(subject):
        return all(pattern[i] == '*' for i in range(p, len(pattern)))

    if pattern[p] in (subject[s], '?'):
        return recur(p + 1, s + 1)
    if pattern[p] == '*':
        return recur(p + 1, s) or recur(p, s + 1)

    return False
