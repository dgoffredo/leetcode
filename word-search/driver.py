import naive

board = [
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

solution = naive.Solution()

assert solution.exist(board, "ABCCED")
assert solution.exist(board, "SEE")
assert not solution.exist(board, "ABCB")