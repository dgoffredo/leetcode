from typing import List


class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if len(digits) == 0:
            return []

        return list(bannanaphone(int(char) for char in digits))


def bannanaphone(digits):
    letters = [0, 0, 'abc', 'def', 'ghi', 'jkl', 'mno', 'pqrs', 'tuv', 'wxyz']
    current = [[digit, 0] for digit in digits]

    while True:
        yield ''.join(letters[digit][index] for digit, index in current)
        
        for i, entry in enumerate(current):
            digit, index = entry
            if index == len(letters[digit]) - 1:
                # carry over, unless we're last, in which case we're done
                if i == len(current) - 1:
                    return

                entry[1] = 0
            else:
                # no carry; just increment and off we go to the next
                entry[1] += 1
                break

