# leetcode.com boilerplate
from typing import List


class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        return largest_colinear_subset_size(points)


from collections import Counter
import math


def largest_count(counter):
    most_common = counter.most_common(1)
    if len(most_common) == 0:
        return 0

    (_, count), *_ = most_common
    return count


def divide(numerator, denominator):
    common_factor = math.gcd(numerator, denominator)
    if common_factor == 0:
        common_factor = 1
    return numerator // common_factor, denominator // common_factor


def linear_slope(p1, p2):
    # Return the numerator and denominator of the slope of the line connecting
    # the specified points p1 and p2, where p1 and p2 are each lists [x, y] of
    # two integers.  The two numbers returned are coprime.
    x1, y1 = p1
    x2, y2 = p2
    return divide(y2 - y1, x2 - x1)


def y_intercept(p, slope):
    """Return the y intercept of the line passing through the specified point p
    and having the specified slope.
    """
    x0, y0 = p
    dy, dx = slope

    # The y intercept is
    #
    #     y_intecept = y0 - slope * x0
    #
    # but keep in mind that slope is a pair of (numerator, denominator), so we
    # have to do the gcd calculation ("normalized rational arithmetic").  The
    # result has a nice symmetry to it:
    #
    #     y_intercept = (y0*dx - x0*dy) / dx
    
    return divide(y0*dx - x0*dy, dx)


def linear_equation(p1, p2):
    """Return a tuple containing the slope and the y intercept of the line
    joining the specified points p1 and p2, where each point is a list of two
    integers [x, y].
    """
    slope = linear_slope(p1, p2)
    return slope, y_intercept(p1, slope)


def largest_colinear_subset_size(points):
    """The plan is to go over all n(n-1)/2 unordered pairs of points in the
    input, and for each pair find the equation of the line connecting them,
    and store that equation in a normalized form.  This way, we can keep track
    of the number of times each _line_ appears, and take the max from that.
    Then we can calculate the number of points corresponding to that "line
    count" (they're triangle numbers).
    """

    # First, an edge case:
    if len(points) < 2:
        return len(points)

    line_counts = Counter()

    # i < j < len(points), so that once we encounter (p1, p2), we don't have to
    # worry about (p2, p1) because we arrange things so that p1 always comes
    # before p2 in the input.
    for i in range(len(points)):
        for j in range (i + 1, len(points)):
            # TODO: This "skip it" logic might not be correct depending on how
            #       duplicate points are expected to be counted.
            if points[i] != points[j]:
                line_counts[linear_equation(points[i], points[j])] += 1

    high_score = largest_count(line_counts)

    # high_score is the number of times we calculated the equation of a
    # particular line.  That is more often than there are points on the line;
    # for example, if a line contains points "a b c d", then we would encounter
    # that line for each of "a b", "b c", "c d", "a c", "b d", and "a d".  This
    # is why this solution is so inefficient.
    # In the example above, the line is encountered 6 times, while the number
    # of points on the line (which is the answer we seek) is 4.  In general,
    #
    #     high_score = (num_points * (num_points - 1)) / 2
    #
    # and so
    #
    #     num_points = 1 + sqrt(1 + 8*high_score) / 2
    #

    num_points = 1 + int(math.sqrt(1 + 8*high_score)) // 2
    return num_points
