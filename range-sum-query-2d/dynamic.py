"""Oh, I see.

They're giving me matrix ahead of time so that I can calculate the lookup table
once and then they can query `sumRegion` multiple times.

This has me thinking -- I can use `matrix` itself to store the sums.  This way
I use even less memory.
"""


from typing import List


class NumMatrix:
    def __init__(self, matrix: List[List[int]]):
        # `self.table` is how we'll refer to the lookup table in `sumRegion`.
        self.table = matrix

        # Stupid corner case not mentioned in the problem description:
        if len(matrix) == 0 or len(matrix[0]) == 0:
            return

        # The game is for each matrix[i][j] to be the sum of the rectangle
        # whose top left corner is (0, 0) and whose bottom right corner is
        # (i, j).  First we calculate the values for the first row and the
        # first column, and then for all of the interior positions.

        # First row.
        total = 0
        for j in range(len(matrix[0])):
            total += matrix[0][j]
            matrix[0][j] = total

        # First column.  It's ok that we calculate (0, 0) twice.
        total = 0
        for i in range(len(matrix)):
            total += matrix[i][0]
            matrix[i][0] = total

        # Other values.
        for i in range(1, len(matrix)):
            for j in range(1, len(matrix[0])):
                # The sum of the rectangle from (0, 0) to (i, j) is just the
                # value at (i, j) plus the sum of the rectangles ending above
                # and to my left, but then I've added up the upper-left
                # rectangle twice, so I subtract it once.
                matrix[i][j] = (  matrix[i][j] 
                                + matrix[i - 1][j]
                                + matrix[i][j - 1]
                                - matrix[i - 1][j - 1])


    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        """
        +---+---+---+---+---+---+---+
        |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+
        |   | D |   | C |   |   |   |
        +---+---+---+---+---+---+---+
        |   |   | X |   |   |   |   |
        +---+---+---+---+---+---+---+
        |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+
        |   | B |   | A |   |   |   |
        +---+---+---+---+---+---+---+

        The key observation of this solution is that to get the sum of the
        rectangle from X to A, you do the following using `self.table`:

            Sum(X, A) = A - B - C + D

        A is too much, so you remove the top stuff and the left stuff by
        substracting B and C, but then you subtracted the upper left stuff
        twice, so you add it back once so that it was subtracted only once.
        """
        m = self.table  # for brevity

        # Stupid corner case not mentioned in the problem description:
        if len(m) == 0 or len(m[0]) == 0:
            return 0

        # If the specified rectangle is in the first row or in the first row,
        # those are special cases.
        B = 0
        if col1 != 0:
            B = m[row2][col1 - 1]

        C = 0
        if row1 != 0:
            C = m[row1 - 1][col2]

        D = 0
        if row1 != 0 and col1 != 0:
            D = m[row1 - 1][col1 - 1]

        # print({'B': B, 'C': C, 'D': D})

        return m[row2][col2] - B - C + D
        

# Your NumMatrix object will be instantiated and called as such:
# obj = NumMatrix(matrix)
# param_1 = obj.sumRegion(row1,col1,row2,col2)