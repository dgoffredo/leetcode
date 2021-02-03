from typing import List

class Solution:
    def sequentialDigits(self, low: int, high: int) -> List[int]:
        return sequential_digits(low, high)


def to_digits(integer):
    return [ord(char) - ord('0') for char in str(integer)]


def to_integer(digits):
    return int(''.join(map(str, digits)))


def next(digits):
    # 's' is the first digit
    # 'L' is the number of digits
    s = digits[0]
    L = len(digits)
    if s >= 9 - (L - 1):
        return list(range(1, L + 2))

    # TODO: make sure it's in order

def sequential_digits(low, high):
    low_digits = to_digits(low)
    right_digits = to_digits(high)
    # TODO