class Solution:
    def monotoneIncreasingDigits(self, N: int) -> int:
        return names_are_hard(N)       

def names_are_hard(integer):
    digits = str(integer)

    if len(digits) == 1:
        return integer

    # Since the input will have no more than ten digits, we can do something
    # simple.
    i, j = 0, 1
    for j in range(1, len(digits)):
        i = j - 1
        if digits[i] <= digits[j]:
            continue # monotone increasing

        # j'th is less than i'th.  Set @i to a suitable new digit, and then the
        # rest is all nines.  Then recur.
        new_digit = chr(ord(digits[i]) - 1)
        changed = digits[:i] + new_digit + '9' * (len(digits) - j)
        return names_are_hard(int(changed))

    return int(digits)
