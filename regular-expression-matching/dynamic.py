
# leetcode.com boilerplate
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        return match(p, s)


def match(pattern, subject):
    tokens = parse(pattern)
    # print(tokens)

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


class Star:
    def __init__(self, arg):
        self.arg = arg

    def __repr__(self):
        return f'Star({self.arg})'


def parse(pattern):
    tokens = []
    i = len(pattern) - 1
    while i >= 0:
        if pattern[i] == '*':
            while pattern[i] == '*':
                i -= 1 # guaranteed not to underflow -- pattern assumed valid
            tokens.append(Star(pattern[i]))
        else:
            tokens.append(pattern[i])

        i -= 1

    tokens.reverse()
    return tokens


def match_suffix(p, pattern, s, subject, recur):
    if p == len(pattern):
        return s == len(subject)
    if s == len(subject):
        return all(type(pattern[i]) is Star for i in range(p, len(pattern)))

    if pattern[p] in (subject[s], '.'):
        return recur(p + 1, s + 1)
    if type(pattern[p]) is Star:
        char = pattern[p].arg
        return (recur(p + 1, s) 
                or (char in (subject[s], '.') and recur(p, s + 1)))

    return False
