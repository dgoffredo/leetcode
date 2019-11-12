from typing import List


class Solution:
    def numberOfArithmeticSlices(self, A: List[int]) -> int:
        return num_arithmetic_slices(A)


def num_arithmetic_slices(numbers):
    if len(numbers) < 3:
        return 0

    num_slices = 0
    i, j = 0, 3

    def calculate_delta():
        assert j - i == 3
        left_delta = numbers[i + 1] - numbers[i]
        right_delta = numbers[i + 2] - numbers[i + 1]

        if left_delta == right_delta:
            return left_delta
        else:
            return None

    current_delta = calculate_delta()
    if current_delta is not None:
        num_slices = 1

    while True:
        if current_delta is None:  # We're not in an arithmetic run.
            # Try our luck sliding to the right
            if j == len(numbers):
                break # Can't slide any more

            i += 1
            j += 1
            current_delta = calculate_delta()
            if current_delta is not None:
                num_slices += 1
        else:  # We're in an arithmetic run.
            # Try our luck expanding to the right.
            if j == len(numbers):
                break # Can't expand any more.
            
            delta = numbers[j] - numbers[j - 1]
            j += 1
            if delta == current_delta:
                # Found another element in this same run.  We count this new
                # longest run, and also the smaller ones ending at this new
                # element.
                num_slices += (j - i) - 3 + 1
            else:
                # The current run has ended.  Start beginning at the new delta.
                current_delta = None
                i = j - 2
                j += 1
                if j > len(numbers):
                    break # Won't be finding any more


    return num_slices
