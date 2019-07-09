from typing import List


# leetcode.com boilerplate
class Solution:
    def outerTrees(self, points: List[List[int]]) -> List[List[int]]:
        return convex_hull(points)


def convex_hull(points):
    """The plan is to sort the points lexicographically (i.e. left-to-right,
    top-to-bottom), and then calculate the bottom section of the hull
    separately from the top section. The magic trick of this algorithm is
    that if you run it over the sorted input, you get the bottom of the
    hull, and if you run it over reverse sorted input, you get the top of
    the hull.
    """
    points.sort()
    lower_hull = partial_hull(points)
    upper_hull = partial_hull(reversed(points))

    # Per the problem description, all the points in `points` are distinct, so
    # we can de-duplicate points appearing in both parts of the hull by running
    # through a set.
    complete_hull = set((x, y) for x, y in lower_hull + upper_hull)
    return list(list(point) for point in complete_hull)
    

def partial_hull(points):
    stack = []
    for point in points:
        if len(stack) < 2:
            stack.append(point)
            continue

        stack.append(point)
        # If we're going counter-clockwise or straight, great! If we're going
        # the wrong way, though, then we need to remove the middle point until
        # we're going the right way or until there are too few points left in
        # the stack.
        while len(stack) >= 3 and orientation(*stack[-3:]) == 'clockwise':
            stack.pop(-2)

    return stack


def orientation(start, middle, end):
    product = cross_product(vector_difference(middle, start),
                            vector_difference(end, middle))
    if product > 0:
        return 'counter-clockwise'
    elif product == 0:
        return 'straight'
    else:
        assert product < 0
        return 'clockwise'


def vector_difference(tail, head):
    a0, a1 = tail
    b0, b1 = head
    return [b0 - a0, b1 - a1]


def cross_product(first_vector, second_vector):
    """Ok, it's not a cross product. It's the z-component of the cross product
    of the three-dimensional vectors resulting from embedding the specified
    two-dimensional vectors in the x-y plane.
    """ 
    a0, a1 = first_vector
    b0, b1 = second_vector
    return a0 * b1 - a1 * b0
