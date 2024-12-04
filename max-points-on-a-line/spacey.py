# leetcode.com boilerplate
from typing import List


class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        return largest_colinear_subset_size(points)


from collections import defaultdict
import math


def divide(numerator, denominator):
    common_factor = math.gcd(numerator, denominator)
    if denominator == 0:
        # Don't divide by zero.
        common_factor = 1
    elif denominator < 0:
        # Consider the sign to be always on top.
        common_factor = -common_factor

    return numerator // common_factor, denominator // common_factor


def linear_slope(p1, p2):
    # Return the numerator and denominator of the slope of the line connecting
    # the specified points p1 and p2, where p1 and p2 are each lists [x, y] of
    # two integers.  The two numbers returned are coprime.
    x1, y1 = p1
    x2, y2 = p2
    dy = y2 - y1
    dx = x2 - x1

    # A potential bug would be the assumption that all lines can be expressed
    # as (slope, y_intercept). This excludes vertical lines.  So, vertical
    # lines will need their own representation: ((None, None), x_intercept).
    if dx == 0:
        return None, None
    else:
        return divide(dy, dx)


def intercept(p, slope):
    """Return the x or y intercept of the line passing through the specified
    point p and having the specified slope.
    """
    x0, y0 = p

    if slope == (None, None):
        # The slope is "infinite," i.e. the intercept will be the x intercept
        # rather than the y intercept.
        return x0

    dy, dx = slope

    # The y intercept is
    #
    #     y_intercept = y0 - slope * x0
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
    return slope, intercept(p1, slope)


def largest_colinear_subset_size(points):
    """TODO: document"""

    # First, find how many copies of each point there are in the input.
    duplicities = defaultdict(int)
    for point in points:
        duplicities[tuple(point)] += 1

    distinct_points = list(duplicities.keys())
    lines = {}  # line -> set(points...)

    # i < j < len(points), so that once we encounter (p1, p2), we don't have to
    # worry about (p2, p1) because we arrange things so that p1 always comes
    # before p2 in the input.
    for i in range(len(distinct_points)):
        p1 = distinct_points[i]
        for j in range (i + 1, len(distinct_points)):
            p2 = distinct_points[j]
            equation = linear_equation(p1, p2)
            points_on_line = lines.setdefault(equation, set())
            points_on_line.add(p1)
            points_on_line.add(p2)

    if len(lines) == 0:
        # No lines -> same point -> same line.
        return len(points)

    def score(set_of_points):
        return sum(duplicities[point] for point in set_of_points)

    return max(score(set_of_points) for set_of_points in lines.values())
