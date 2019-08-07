# leetcode.com boilerplate
class Solution:
    def countArrangement(self, N: int) -> int:
        return num_beautiful_arrangements(N)


def num_beautiful_arrangements(n):
    is_marked = [False] * (n + 1)

    def is_candidate(value, i):
        return not is_marked[value] and (value % i == 0 or i % value == 0)

    def recur(i):
        if i == n:
            for value in range(1, n + 1):
                if is_candidate(value, i):
                    yield 1
        else:
            for value in range(1, n + 1):
                if is_candidate(value, i):
                    is_marked[value] = True
                    yield from recur(i + 1)
                    is_marked[value] = False

    return sum(recur(1))
