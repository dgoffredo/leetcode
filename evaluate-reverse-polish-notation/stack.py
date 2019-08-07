import math
from typing import List


# leetcode.com boilerplate
class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        return evaluate(tokens)


def evaluate(tokens):
    stack = []
    for token in tokens:
        if token == '+':
            b, a = stack.pop(), stack.pop()
            stack.append(a + b)
        elif token == '-':
            b, a = stack.pop(), stack.pop()
            stack.append(a - b)
        elif token == '*':
            b, a = stack.pop(), stack.pop()
            stack.append(a * b)
        elif token == '/':
            b, a = stack.pop(), stack.pop()
            stack.append(math.trunc(a / b))
        else:
            stack.append(int(token))

    return stack[0]
