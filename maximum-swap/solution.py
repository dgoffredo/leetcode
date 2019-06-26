
class Solution:
    def maximumSwap(self, num: int) -> int:
        return maximum_swap(num)


def maximum_swap(integer):
    digits = [(digit, i) for i, digit in enumerate(str(integer))]
    switch = None # (index from, index to)
    for digit, i in digits[:-1]:
        other, j = max(digits[i+1:])
        if other > digit:
            switch = i, j
            break

    if switch is None:
        return integer
    
    dest, source = switch
    temp = digits[dest]
    digits[dest] = digits[source]
    digits[source] = temp

    return int(''.join(digit for (digit, _) in digits))
