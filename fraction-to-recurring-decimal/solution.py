import math


class Solution:
    def fractionToDecimal(self, numerator: int, denominator: int) -> str:
        return divide(numerator, denominator)


def divide(numerator, denominator):
    if numerator / denominator < 0:
        # It's easier to deal with negatives this way.
        return '-' + divide(abs(numerator), abs(denominator))

    quotient = math.trunc(numerator / denominator)
    remainder = numerator % denominator
    result = str(quotient)

    if remainder == 0:
        return result

    result += '.'

    # Otherwise, we need to do the long division thing.  Also, keep track of
    # our remainders and when we last encountered them, so that if we find the
    # same remainder twice, we notice the cycle and insert the appropriate
    # parentheses.
    remainders = {remainder: len(result)}

    while True:
        new_numerator = remainder * 10
        quotient = math.trunc(new_numerator / denominator)
        remainder = new_numerator % denominator

        result += str(quotient)
        if remainder == 0:
            return result

        index = remainders.get(remainder)
        if index is not None:
            return result[:index] + '(' + result[index:] + ')'

        remainders[remainder] = len(result)
