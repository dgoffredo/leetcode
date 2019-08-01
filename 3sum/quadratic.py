# lol "3sum"


from typing import List


# leetcode.com boilerplate
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        return list(null_triples(nums))


def print(*args, **kwargs):
    pass


def null_triples(numbers):
    """Yield all distinct triples from `numbers` whose sum is zero."""
    lookup = lookup_table(numbers)
    yield from three_sum(numbers, lookup, 0)


def three_sum(numbers, lookup, k):
    solutions = set()  # set of sets of three numbers

    for i in range(len(numbers)):
        print(f'looking at index {i}, which is {numbers[i]}')
        print(f'That means the sum to look for is {k - numbers[i]}')
        for (j, m) in two_sum_index(numbers, lookup, k - numbers[i]):
            print(f'two_sum_index({k - numbers[i]}) -> {(j, m)}')
            if i in (j, m):
                continue

            values    = [numbers[i], numbers[j], numbers[m]]
            candidate = frozenset(values)
            if candidate not in solutions:
                solutions.add(candidate)
                yield values


def lookup_table(numbers):
    table = {}
    for i, number in enumerate(numbers):
        table.setdefault(number, set()).add(i)

    return table


def two_sum_index(numbers, lookup, k):
    solutions = set()  # set of sets of two numbers
    print(f'two_sum_index({k})')

    for i in range(len(numbers)):
        indices = lookup.get(k - numbers[i])
        print(f'lookup.get({k - numbers[i]}) -> {indices}')
        if indices is None:
            continue

        for j in indices:
            if j == i:
                continue

            values    = [numbers[i], numbers[j]]
            candidate = frozenset(values)
            if candidate not in solutions:
                solutions.add(candidate)
                yield [i, j]
