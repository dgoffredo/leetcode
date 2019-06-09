
# leetcode.com boilerplate
class Solution:
    def largestRectangleArea(self, heights):
        return largest_rectangle_area(heights)


def largest_rectangle_area(heights):
    """The idea is to maintain a stack of "(since_when, height)" tuples. When
    a higher value is encountered, a new tuple is pushed onto the stack. When
    a lower value is encountered, this ends the "streak" of one or more of the
    previous tuples, so pop from the stack while the popped heights are greater
    than the most recently encountered height, and for each reason about the
    relevant rectangle, and keep track of the largest area so encountered. At
    the end of the input, act as though there is a zero-height additional
    input, thus draining the entire stack to reason about any remaining
    rectangles. 
    """
    stack = []
    max_area = 0
    for i, height in enumerate(heights):
        if len(stack) == 0:
            stack.append((i, height))
            continue

        prev_i, prev_height = stack[-1]
        if prev_height < height:
            stack.append((i, height))
            continue

        prev_prev_i = i
        while prev_height > height:
            area = prev_height * (i - prev_i)
            if area > max_area:
                max_area = area

            stack.pop()
            prev_prev_i = prev_i
            if len(stack) == 0:
                break

            prev_i, prev_height = stack[-1]

        if prev_height != height:
            stack.append((prev_prev_i, height))

    # Now we've gotten to the end of the input. Account for any rectangles
    # implied by the remaining tuples in the stack.
    i = len(heights) # one past the last index
    while len(stack) > 0:
        prev_i, prev_height = stack.pop()
        area = prev_height * (i - prev_i)
        if area > max_area:
            max_area = area

    return max_area
        