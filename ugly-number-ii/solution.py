
# leetcode.com boilerplate
class Solution:
    def nthUglyNumber(self, n: int) -> int:
        return ugly_number(n)


def ugly_number(n):
    numbers = set([1])
    new_numbers = set([1])
    while len(numbers) < n:
        new_numbers = (set(2*x for x in new_numbers)
                     | set(3*x for x in new_numbers)
                     | set(5*x for x in new_numbers))
        numbers |= new_numbers

    return sorted(numbers)[n - 1]


